            var map = L.map('map').setView([51.515,-0.105], 15);
            var mapboxUrl = 'http://{s}.tiles.mapbox.com/v3/ankeshanand.map-pm6s6o5g/{z}/{x}/{y}.png'; 
            var tilesUrl = 'http://localhost:8080/tiles/{z}/{x}/{y}.png';
            var cloudmadeUrl = 'http://{s}.tile.cloudmade.com/bd37d29342474accb0e454714e3734f7/22462/256/{z}/{x}/{y}.png';
            var cloudmade = L.tileLayer(cloudmadeUrl, {attribution: 'Map data &copy; <a href="http://openstreetmap.org">OpenStreetMap</a> contributors, <a href="http://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="http://cloudmade.com">CloudMade</a>',
                    maxZoom: 20
                    }).addTo(map);

// control that shows state info on hover
var info = L.control();

info.onAdd = function (map) {
    this._div = L.DomUtil.create('div', 'info');
    this.update();
    return this._div;
};

info.update = function (props) {
    this._div.innerHTML = '<h4>Cloak Simulation (Without Noise)</h4>' +  (props ?
            '<b>Density: ' + props.density + ' people / sq.' + '<br><b>Count: ' + props.count
            : 'Hover over a square');
};

info.addTo(map);
L.control.scale().addTo(map);
// get color depending on population density value
function getColor(d) {
    return d > 500 ? '#800026' :
        d > 200  ? '#BD0026' :
        d > 100  ? '#E31A1C' :
        d > 50  ? '#FC4E2A' :
        d > 20   ? '#FD8D3C' :
        d > 10   ? '#FEB24C' :
        d > 1   ? '#FED976' :
        '#FFEDA0';
}

function getOpacity(d) {
    if(d == 0)
    {
        return 0.0;
    }
    else
    {
        return 0.8;
    }
}

function style(feature) {
    return {
fillColor: getColor(feature.properties.density),
               weight: 0.5,
               opacity: 1,
               color: 'white',
               dashArray: '3',
               stroke: false,
               fillOpacity: getOpacity(feature.properties.density)
    };

}	

function highlightFeature(e) {
    var layer = e.target;

    layer.setStyle({
weight: 5,
color: '#666',
dashArray: '',
fillOpacity: 0.7
});

if (!L.Browser.ie && !L.Browser.opera) {
    layer.bringToFront();
}

info.update(layer.feature.properties);
}

var geojson;

function resetHighlight(e) {
    geojson.resetStyle(e.target);
    info.update();
}

function zoomToFeature(e) {
    map.fitBounds(e.target.getBounds());
}

function onEachFeature(feature, layer) {
    layer.on({
mouseover: highlightFeature,
mouseout: resetHighlight,
click: zoomToFeature
});
}


geojson = L.geoJson(locationData, {
style: style,
onEachFeature: onEachFeature
}).addTo(map);

var geojson_noise = L.geoJson(locationData_Noise,{
style:style,
onEachFeature: onEachFeature
}).addTo(map);

var legend = L.control({position: 'bottomright'});

legend.onAdd = function (map) {

    var div = L.DomUtil.create('div', 'info legend'),
        grades = [0, 10, 20, 40, 50, 100, 200, 500],
        labels = [];

    // loop through our density intervals and generate a label with a colored square for each interval
    for (var i = 0; i < grades.length; i++) {
        div.innerHTML +=
            '<i style="background:' + getColor(grades[i] + 1) + '"></i> ' +
            grades[i] + (grades[i + 1] ? '&ndash;' + grades[i + 1] + '<br>' : '+');
    }

    return div;
};

legend.addTo(map);

function getNewData(url){
    map.removeLayer(geojson);
    geojson = L.geoJson(url,{
style:style,
onEachFeature: onEachFeature
}).addTo(map);
}

var baseMaps = {
    "Without Noise": geojson,
    "With Noise": geojson_noise 
};
L.control.layers(baseMaps).addTo(map);
