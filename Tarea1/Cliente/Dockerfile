FROM centos:latest

ENV container docker
WORKDIR  /etc/yum.repos.d/ 
RUN sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* 
RUN sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN yum update -y


RUN yum install gcc -y

RUN mkdir -p ./home/Cliente \
    && chmod 775 ./home/Cliente -R 

COPY . /home/Cliente/

WORKDIR /home/Cliente

RUN gcc Client2.c -o Client2
