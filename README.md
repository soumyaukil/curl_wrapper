# curl_wrapper

## Pre-requisite 
* Linux machine
* GNU g++ 4.9 or above
* cmake 2.8 or above
* libcurl library. If not installed in your machine, please install ```yum install libcurl``` or ```apt-get install libcurl```
* bash shell

## Building process
* Go to source code. You will have three directories i.e. ```src```, ```include```, ```bin```. There is one ```CMakeLists.txt```. 
* Create a directory in source directory. ```mkdir build```
* Go to inside ```build``` that you have created above. Run ```cmake ..```.
* After above command is successful, run ```make```.
* This will take couple of minutes and then compilation will be finished.

## How to Run?
* Once building is successful, you go back to source code folder once again. Do ```cd ..```. You will see there is one ```install``` dirctory 
has been created.
* Go to ```install``` directory. You will see one binary ```pencildata_v1.2.0``` present there.
* If you jwant to run ```./pencildata_v1.2.0```, you would need to provide ```username```, ```password``` and ```filename``` which will be hashed.
* To run ```pencildata_v1.2.0```, you need to run this command: ```./pencildata_v1.2.0 <username> <password> <filename>```
