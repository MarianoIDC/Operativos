FROM centos:latest

ENV container docker
WORKDIR  /etc/yum.repos.d/ 
RUN sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* 
RUN sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN yum update -y

WORKDIR /home/
RUN yum install gcc -y
