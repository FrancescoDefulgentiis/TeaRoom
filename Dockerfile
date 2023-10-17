#we are basically creating a custom docker image

#choose the base image
FROM ubuntu:20.04

#i guess we are choosing the name of the working directory
WORKDIR /Tearoom

#this should copy all the files from the current directory to the working directory
COPY . /home/tearoom

#this should install all the dependencies, i dont have none right now, but i will have to figura out how to install opencv
#RUN apt update && sudo apt install -y cmake g++ wget unzip 
#RUN wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip 
#RUN unzip opencv.zip
#RUN mkdir -p build && cd build
#RUN cmake ../opencv-4.x
#RUN cmake --build .

#we repeat this command to access the second phase, which is the runtime phase, i guess



