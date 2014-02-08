#include "database.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include "noise.h"
#include "user.h"

database::database()
{
    offset_min_la = 500;
    offset_max_la = -500;
    offset_min_lo = 500;
    offset_max_lo = -500;
    cells_x = 16;
    cells_y = 16;
    grid_unit = 64;
}

database * database::_instance = 0;


database *database::Instance()
{
    if(_instance==0)
        _instance = new database;
    return _instance;
}

void database::computeList(const char* filename)
{
    //Use the JSON Parser to generate the database
    Json::Value root;
    Json::Reader reader;
    std::ifstream dataFile("location_data_large.json");
    bool parsingSuccessful = reader.parse(dataFile,root,true);
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << reader.getFormatedErrorMessages()
               << "\n";
    }
    const Json::Value location = root["location"];
    for(long int index=0; index<location.size();index++)
    {
        dataPoint tempPoint;
        tempPoint.la = location[index]["la"].asDouble();
        if(tempPoint.la == 0)
        {
            continue;
        }
        tempPoint.lo = location[index]["lo"].asDouble();
        if(tempPoint.lo < -0.2)
        {
            continue;
        }
        tempPoint.user_id = QString::fromStdString(location[index]["ui"].asString());
       // tempPoint.time = QString::number(location[index]["t"].asInt());
       // tempPoint.u_time = QString::number(location[index]["ut"].asInt());
        points.push_back(tempPoint);
    }
   std::cout<<"size="<<location.size()<<"\n";
}

void database::computeOffsets()
{

    for(int i=0;i<points.size();i++)
    {
        if(points[i].la < offset_min_la)
        {
            offset_min_la = points[i].la;
        }
        if(points[i].la > offset_max_la)
        {
            offset_max_la = points[i].la;
        }
        if(points[i].lo < offset_min_lo)
        {
            offset_min_lo = points[i].lo;
        }
        if(points[i].lo > offset_max_lo)
        {
            offset_max_lo = points[i].lo;
        }
    }
    std::cout << offset_min_la << "," << offset_max_la <<"\n";
    std::cout << offset_min_lo << "," << offset_max_lo <<"\n";
    range_la = offset_max_la - offset_min_la;
    range_lo = offset_max_lo - offset_min_lo;
    range = std::max(range_la,range_lo);
    std::cout<<"range_la="<<range_la<<"\t"<<"range_lo="<<range_lo<<"range="<<range<<"\n";

    if( range_la > range_lo )
    {
        double diff = range_la - range_lo;
        std::cout<<"diff="<<diff<<"\n";
        offset_min_lo = offset_min_lo - (diff/2.00) - (range/10.00); // making sure the grid is square
        offset_max_lo = offset_max_lo + (diff/2.00) + (range/10.00); //and adding margins to it
        offset_min_la = offset_min_la - (range/10);
        offset_max_la = offset_max_la + (range/10);
            range = offset_max_la - offset_min_la ;

    }

    else
        {
        std::cout<< "here" << "\n";
        double diff = range_lo - range_la;
        offset_min_la = offset_min_la - (diff/2) - (range/10);
        offset_max_la = offset_max_la + (diff/2) + (range/10);
        offset_min_lo = offset_min_lo - (range/10);
        offset_max_lo = offset_max_lo + (range/10);
        range = offset_max_lo - offset_min_lo ;
    }
    std::cout<<offset_min_la<<"\n"<<offset_max_la<<"\n"<<offset_min_lo<<"\n"<<offset_max_lo<<"\n";

}

void database::generateGrid()
{
    int size = 1;
    while( size  <= (grid_unit) )
    {
        std::vector<square> temp_row;
        for(int i=1;i<=grid_unit/size;i++)
        {
            for(int j=1;j<=grid_unit/size;j++)
            {
                square *temp = new square;
                temp->size = size;
                temp->offset_x = offset_min_la + (i-1)*(range/(grid_unit/size));
                temp->offset_y = offset_min_lo + (j-1)*(range/(grid_unit/size));
                temp->row = i;
                temp->column = j;
                temp_row.push_back(*temp);
                delete temp;
            }

        }
        grid.push_back(temp_row);
        temp_row.clear();
        size = 2 * size;
    }
}

void database::aggregateForAll()
{
    for(int index=0; index<points.size(); index++)
    {
        double lat = points[index].la;
        double lon = points[index].lo;
        int size=1;
        int count=0;
        while(size <= grid_unit)
        {
            double square_span = (double(size)/grid_unit) * range ;
            int row = (lat - offset_min_la) / square_span + 1;
            int column = (lon - offset_min_lo) / square_span + 1 ;
          //  std::cout<<"count:"<<count<<"para: "<<(8/size)*(row-1) + (column-1)<<"\n";
            grid[count][(64/size)*(row-1) + (column-1)].count++;
            //std::cout<<"id="<<grid[count][(8/size)*(row-1) + (column-1)].id;
            size = size * 2;
            count++;
        }
    }
}

void database::displayCounts()
{
    int size=1;
    int count = 0;
    while(size <= grid_unit)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            //std::cout<<grid[count][i].id<<"\n";

              std::cout<<"Square:"<<"Row ="<<grid[count][i].row<<" Column:"<<grid[count][i].column<<" Size:"<<grid[count][i].size<<" Density:"<<grid[count][i].density<<"Count:" <<grid[count][i].count<<"\n";
        }

        size = size * 2;
        count++;
    }
}

void database::setParents()
{
    int size=1;
    int count = 0;
    while(size < grid_unit)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            for(int j=0;j<(grid_unit*grid_unit)/(size*size*4);j++)
            {
                if((grid[count+1][j].offset_x<=grid[count][i].offset_x)&&(grid[count+1][j].offset_y<=grid[count][i].offset_y))
                {
                   grid[count][i].parentId = grid[count+1][j].id;
                   grid[count][i].parentParam1 = count+1;
                   grid[count][i].parentParam2 = j;
                   std::cout <<count << "," << i << "->" << grid[count][i].parentParam1 << "," << grid[count][i].parentParam2 <<"\n" ;
                }
            }
        }
        size = size * 2;
        count++;
    }
}

void database::kAnonymize(int k)
{
    int size=1;
    int count=0;
    while(size <= grid_unit)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            if(grid[count][i].count < k)
            {
                grid[count][i].density=0;
            }
        }
        size = size * 2;
        count++;
    }

    size=grid_unit/2;
    count=4;
    while(size >= 1)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            if(grid[count][i].density == 0)
            {
                setParentCount(count,i,k);
                //std::cout<<"count= "<<count<<" i= "<<i<<"\n";
            }
        }
        size = size/2;
        count--;
    }
}

void database::newAnonymize(int k)
{
    int size = 1;
    int count = 0;

    while(size < grid_unit)
    {
        for(int i=0; i<grid_unit*grid_unit/(size*size); i++)
        {
            if(grid[count][i].count >= k)
            {
                grid[count][i].isSet = 1;
                grid[count][i].density = grid[count][i].count / (size*size) ;
                std::cout <<" Updating Parent count for " <<count << "," <<i <<"\n";
                updateParentCounts(count,i);

            }

            else{
                grid[count][i].density = 0;
            }
        }
        count++;
        size = size * 2;
    }

    size=grid_unit/2;
    count=5;
    while(size >= 1)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            if(grid[count][i].density == 0)
            {
                setParentCount(count,i,k);
                //std::cout<<"count= "<<count<<" i= "<<i<<"\n";
            }
        }
        size = size/2;
        count--;
    }

}

void database::updateParentCounts(int param1, int param2)
{
    int perm1 = param1;
    int perm2 = param2;
    int parent_size = grid[param1][param2].size;
    while(parent_size < grid_unit)
    {
      int  parentParam1 = grid[param1][param2].parentParam1;
      int  parentParam2 = grid[param1][param2].parentParam2;
      std::cout << "Count Updated for " << parentParam1 <<"," <<parentParam2 << "from" << grid[parentParam1][parentParam2].count ;
      grid[parentParam1][parentParam2].count = grid[parentParam1][parentParam2].count - grid[perm1][perm2].count;
      std::cout << "->" << grid[parentParam1][parentParam2].count <<"\n";
      param1 = parentParam1;
      param2 = parentParam2;
      parent_size  = parent_size * 2;
    }

}

void database::setParentCount(int param1,int param2,int k)
{
    int parent_x = grid[param1][param2].parentParam1;
    int parent_y = grid[param1][param2].parentParam2;

    if(parent_x == -1 || parent_y == -1)
    {
       ;
    }
    else if(grid[parent_x][parent_y].count >= k)
    {
        //grid[param1][param2].count = grid[parent_x][parent_y].count;
        grid[param1][param2].density = grid[parent_x][parent_y].density;
        std::cout <<"param1= "<<param1<<" param2= "<<param2<<" density= "<<grid[param1][param2].density <<"\n";

    }
    else{
         setParentCount(parent_x,parent_y,k);
    }

}

void database::setDensities()
{
    int size=1;
    int count=0;
    while(size <= grid_unit)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            grid[count][i].density = (double)grid[count][i].count/(double)(grid[count][i].size*grid[count][i].size);
            //std::cout<<"count= "<<count<<" i= "<<i<<" number= "<<grid[count][i].count<<" density= "<<grid[count][i].density<<"\n";
        }
        size = size * 2;
        count++;
    }
}

void database::addNoise(double mean,double sigma)
{
    std::ofstream difference;
    difference.open("/opt/lampp/htdocs/CloakSimulation/difference.tsv");
    difference<<"Square\t"<<"WithoutNoise\t"<<"WithNoise\n";
    int size=1;
    int count=0;
    noise Noise;
    while(size <= grid_unit)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            grid[count][i].orgDensity = grid[count][i].density;
            grid[count][i].density += Noise.GetRandomNoise(mean,sigma);

        }
        size = size * 2;
        count++;
    }
    std::ofstream outputData;
    outputData.open("/opt/lampp/htdocs/CloakSimulation/outputData2.csv");
    outputData <<"Row,"<<"Column,"<<"Density\n";
    size=1;
    count=0;
    while(size == 1)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            outputData <<grid[count][i].row<<","<<grid[count][i].column<<","<<grid[count][i].density<<"\n";
            //std::cout<<grid[count][i].row<<","<<grid[count][i].column<<","<<grid[count][i].density<<"\n";
            difference <<i <<"\t" <<grid[count][i].orgDensity <<"\t" <<grid[count][i].density <<"\n";
        }
        size = size * 2;
        count++;
    }
    outputData.close();
}

void database::exportCSV()
{
    std::ofstream outputData;
    outputData.open("/opt/lampp/htdocs/CloakSimulation/outputData3.csv");
    outputData <<"Row,"<<"Column,"<<"Density\n";
    int size=1;
    int count=0;
    while(size == 1)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            outputData <<grid[count][i].row<<","<<grid[count][i].column<<","<<grid[count][i].density<<"\n";
            //std::cout<<grid[count][i].row<<","<<grid[count][i].column<<","<<grid[count][i].density<<"\n";
        }
        size = size * 2;
        count++;
    }
    outputData.close();
}

void database::exportGeoJSON(std::string filename)
{
    std::ofstream geoData;
    int size=1;
    int count=0;
    int id=1;
    std::string path = "/opt/lampp/htdocs/CloakSimulation/";
    path.append(filename);
    std::cout << filename <<"\n" ;
    geoData.open(path.c_str());
    geoData << "var locationData = " ;
    geoData << "{\"type\":\"FeatureCollection\",\"features\":[" <<"\n";
    while(size == 1)
    {
        for(int i=0;i<(grid_unit*grid_unit)/(size*size);i++)
        {
            geoData << "{\"type\":\"Feature\",\"id\":\"" << id <<"\",";
            geoData << "\"properties\":{\"density\":" << grid[count][i].density << ",\"count\":" << grid[count][i].count <<  "},";
            geoData << "\"geometry\":{\"type\":\"Polygon\",\"coordinates\":[[" ;
            geoData << "[" << grid[count][i].offset_y << "," << grid[count][i].offset_x << "]," ;
            geoData << "[" << grid[count][i].offset_y + range/grid_unit << "," << grid[count][i].offset_x << "],";
            geoData << "[" << grid[count][i].offset_y + range/grid_unit << "," << grid[count][i].offset_x + range/grid_unit << "],";
            geoData << "[" << grid[count][i].offset_y  << "," << grid[count][i].offset_x + range/grid_unit << "]";
            geoData << "]]}}" ;
            if(id != grid_unit*grid_unit)
            {
                geoData << "," ;
            }
            geoData << "\n" ;
            id++;
        }

        size = size * 2;
        count++;
    }
    geoData << "]};" ;
    geoData.close();
}

void database::newParser()
{
    //Use the JSON Parser to generate the database
    Json::Value root;
    Json::Reader reader;
    std::ifstream dataFile("location_data_large.json");

    bool parsingSuccessful = reader.parse(dataFile,root,true);
    if ( !parsingSuccessful )
    {
        // report to the user the failure and their locations in the document.
        std::cout  << reader.getFormatedErrorMessages() << "\n";
    }

    const Json::Value location = root["location"];
    for(long int index=0; index<location.size();index++)
    {

        dataPoint tempPoint;
        tempPoint.la = location[index]["la"].asDouble();
        if(tempPoint.la == 0)
        {
            continue;
        }
        tempPoint.lo = location[index]["lo"].asDouble();
        if(tempPoint.lo < -0.2)
        {
            continue;
        }
        tempPoint.user_id = QString::fromStdString(location[index]["ui"].asString());
        tempPoint.time = location[index]["t"].asInt();
        tempPoint.u_time = location[index]["ut"].asInt();

        user tempUser;
        if(users.size() == 0)
        {
            tempUser.userId = tempPoint.user_id;
           // tempUser.latestTime = tempPoint.time;
            tempUser.myPlaces.push_back(tempPoint);
            users.push_back(tempUser);
        }
        for(int i=0; i<users.size();i++){
            if(users[i].userId == tempPoint.user_id)
            {
                users[i].myPlaces.push_back(tempPoint);
                //if(tempPoint.time > users[i].latestTime){
                    //users[i].latestTime = tempPoint.time;
                //}
            }
            else{
                tempUser.userId = tempPoint.user_id;
               // tempUser.latestTime = tempPoint.time;
                tempUser.myPlaces.push_back(tempPoint);
                users.push_back(tempUser);
            }

        }
    }


}

void database::exportPointMarkers()
{
    std::ofstream markers;
    markers.open("/opt/lampp/htdocs/CloakSimulation/data/markers.js");
    markers << "var markers = " ;
    markers << "{\"type\":\"FeatureCollection\",\"features\":[" <<"\n";
    int id = 1;

    for(int i=0;i<=points.size();i++)
    {
        markers << "{\"type\":\"Feature\",\"id\":\"" << id <<"\",";
        markers << "\"properties\":{\"popupContent\":" << "This is a point." <<  "},";
        markers << "\"geometry\":{\"type\":\"Point\",\"coordinates\":[" << points[i].lo <<"," << points[i].la << "]" << "}" ;

        if(id!=points.size())
        {
            markers << ",";
        }
        markers << "\n";
        id++;
    }

    markers << "]};" ;
    markers.close();
}
