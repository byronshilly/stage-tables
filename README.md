# Stage Tables Implementation in C

This project is an experimental implementation of a "Stage Table" runner, intended to successfully execute large, monolithic, long-running operations in a safer manner. 

This is not necessarily something new, but rather a framework that enforces a philosophy of safety on long-running error-prone operations, such as system upgrades, application deployments, etc. 

The idea is to break up long-running operations into divisible blocks called "stages", each with predefined inputs/outputs. The runner provides a framework for defining stage logic and I/O, and also provides mechanisms that allow stages to communicate with future stages (i.e. if something doesn't go quite right in stage 2, stage 7 might want to know so it can do something differently). 
