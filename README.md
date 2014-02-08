CloakRealtimeSimulation
=======================

This repository contains a simulation of how the cloak would deal with realtime data.

We are working with a dataset from [DFKI](http://www.dfki.de/web). The dataset is proprietary, and should not under any circumstances with shared outside Aircloak.

As the dataset is about an order of magnitude larger when decompressed, we only include the compressed version in this repository. Work with the uncompressed version locally, but please do not check it in to the repository.

The data is a dump from MongoDB and has the format:

- ui: User id
- lo: Longitude
- la: Latitude
- b: Bearing/Heading (in degrees – 90° is East)
- p: Precision of location (in m)
- v: Speed
- t: Timestamp of datapoint
- ut: Timestamp at which the data was uploaded