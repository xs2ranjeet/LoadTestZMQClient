//g++ -g -std=c++11 zmqClient.cpp -o zm -lzmq -lzmqpp -lboost_unit_test_framework -lpthread -lboost_system -lboost_thread

#include <iostream>
#include <string>
#include <mutex>
#include <vector>
#include <deque>
#include <condition_variable>
#include <thread>
#include <zmqpp/zmqpp.hpp>
#include <zmqpp/curve.hpp>
#include <zmqpp/proxy.hpp>
#include <zmqpp/message.hpp>
#include <fstream>
#include <stdio.h>
#include <string.h>
// #include "base64.h"
// #include <stdio.h>
#include <unistd.h>
// #include <getopt.h>
#ifndef _BSD_SOURCE
#define _BSD_SOURCE
#endif
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include<stdio.h> 
#include<stdlib.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<string.h>  
#include<netinet/in.h>  
#include<netdb.h>
  
#include <cstdlib>
#include <string>
#include <iostream>
#include <thread>
#include <signal.h>

#include <zmqpp/zmqpp.hpp>
#include <zmqpp/curve.hpp>
#include <zmqpp/proxy.hpp>
#include <zmqpp/message.hpp>

//#include <cpp_redis/cpp_redis>

#define BUF_SIZE 4096
  
// Number of messages to push
//const uint64_t messages = 1e7;
const uint64_t messages = 5;

// Short message to send
const std::string short_message = "hello world!";
// Timeout for polling in milliseconds

// const long thread_count = 2;
const std::string payload = "{\"c_ids\":[\"34\"],\"ver\":\"\"}";
const std::string ackpayload = "{\"c_ids\":[\"35\"],\"ver\":\"1.0\"}";
// Timeout for polling in milliseconds
const long max_poll_timeout = 1000*60*100;
const long thread_count = 1000;

void zidFileRead(std::string filename, long start, long end){
	std::ifstream fin(filename);
	if(fin){
		fin.seekg(0, fin.end);
		int length = fin.tellg();
		std::cout<<"length of file: "<< length<<"\n";
		fin.seekg(0, fin.beg);
		for(int i = start; i < end; ++i ){
			std::string line; 
			getline(fin, line);
			std::cout<<line<<"\n";
		}

		fin.seekg(17*3, fin.beg);
		// std::cout<<"=============================\n";
		for(int i = start+3; i < end; ++i ){
			std::string line; 
			getline(fin, line);
			// std::cout<<line<<"\n";
		}
	// for(std::string line; getline(fin, line);)
	// 	std::cout<<line<<"\n";

	fin.close();
}

}

void test(){

}


// class client{
// public:
// 	client(std::string& filename, std::string& endpoint, int startid, int endid, int thCount, std::string& payload) 
// 			filename(filename), endpoint(endpoint), startid(startid), endid(endid),thCount(thCount), payload(payload){

// 	}
// 	void start(){
// 	auto pusher_func = [&]( int id, const std::string& identity ) {
// 		dealer[id]= new zmqpp::socket(context, zmqpp::socket_type::dealer);
// 		dealer[id]->set(zmqpp::socket_option::identity, identity);
// 		try{
// 			dealer[id]->connect("tcp://52.203.194.245:5000");
// 			poller.add(*dealer[id]);
// 			// auto remaining = 5;//messages;
// 			zmqpp::message message;
// 			zmqpp::message out_msg(std::to_string(11), payload);
// 			dealer[id]->send(out_msg);
// 			logger->clientCount++;
// 		}catch(...){
// 			std::cout<<"Client max connection exceed. Stop creating more clients\n";
// 			stopMoreClientCreate = true;	
// 		}
// 	};
// 	std::ifstream fin(filename);
// 	if(!fin)
// 	{
// 		std::cerr<<"Error: ZID File doesn't exist: "<< filename<<"\n";
// 		return;
// 	}
// 	fin.seekg(17*start, fin.beg);
// 	std::thread th[thread_count];
// 	for(int i = 0; i < thread_count; i++){
// 		std::string line;
// 		getline(fin, line);
// 		th[i] =  std::thread(pusher_func, i, line);
// 		// std::this_thread::sleep_for(std::chrono::milliseconds(500));
// 	}
// 	fin.close();
// 	for(int i = 0; i < thread_count && stopMoreClientCreate ==  false; i++)
// 		th[i].join();
// 	}
// 	void startPoller(){
// 	zmqpp::message zmsg;
// 	while(poller.poll(exitCondition))
// 	{
// 		for(int i = 0; i < thread_count; i++){
// 			if(poller.has_input(*dealer[i])){
// 				dealer[i]->receive(zmsg);
// 				if(zmsg.parts() == 2 && zmsg.size(0)==2 && zmsg.size(1)==620){
// 					++processed;
// 					logger->response++;
// 					if(logger->dealer[i] == false){
// 						logger->dealer[i] = true;
// 						// logger->error--;
// 					}
// 					else
// 						logger->responseDup++;	
// 					 zmqpp::message message;
// 					 zmqpp::message out_msg(std::to_string(12));
// 					 dealer[i]->send(out_msg);
// 				}
// 			}
// 		}

// 	}

// 	}
// private:
// 	std::string identity;
// 	std::string endpoint;
// 	int thCount;
// 	std::string payload;
// 	static std::atomic uint64_t processed;
// 	zmqpp::context context;
// 	zmqpp::socket *dealer[thread_count];
// 	zmqpp::poller poller;

// };

void client_func(std::string filename, long start, long end){
	// boost::timer t;
	zmqpp::context context;
	zmqpp::socket *dealer[thread_count];
	zmqpp::poller poller;
	// context.set(zmqpp::context_option::max_sockets, 1000000);
		// std::cout<<"Max Socket can connect: "<< context.get(zmqpp::context_option::max_sockets)<<std::endl;

	auto pusher_func = [&]( int id, const std::string& identity ) {
		dealer[id]= new zmqpp::socket(context, zmqpp::socket_type::dealer);
		dealer[id]->set(zmqpp::socket_option::identity, identity);

		dealer[id]->connect("tcp://52.203.194.245:5000");
		//dealer[id]->connect("tcp://52.55.204.235:5000");
		poller.add(*dealer[id]);
		// auto remaining = 5;//messages;
		zmqpp::message message;
			zmqpp::message out_msg(std::to_string(11), payload);
			dealer[id]->send(out_msg);
	};
	std::ifstream fin(filename);
	if(!fin)
	{
		std::cerr<<"Error: ZID File doesn't exist: "<< filename<<"\n";
		return;
	}
	fin.seekg(17*start, fin.beg);
	std::thread th[thread_count];
	for(int i = 0; i < thread_count; i++){
		std::string line;
		getline(fin, line);
		th[i] =  std::thread(pusher_func, i, line);
		// std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	fin.close();
	for(int i = 0; i < thread_count; i++)
		th[i].join();

	uint64_t processed = 0;
	std::string message;
	zmqpp::message zmsg;
	while(poller.poll())
	{
		for(int i = 0; i < thread_count; i++){
			if(poller.has_input(*dealer[i])){
				dealer[i]->receive(zmsg);
				if(zmsg.parts() == 2 )//&& zmsg.size(0)==2 && zmsg.size(1)==620){
				{
					++processed;
					 zmqpp::message message;
					 zmqpp::message out_msg(std::to_string(12), ackpayload);
					 dealer[i]->send(out_msg);
				}
			}
		}

	}

	// double elapsed_run = t.elapsed();

	std::cout<<"ZMQPP: Copy String\n";
	std::cout<<"Messages pushed    : " << processed<<std::endl;
	// std::cout<<"Run time           : " << elapsed_run << " seconds\n";
	// std::cout<<"Messages per second: " << processed / elapsed_run<<"\n";
	for(int i = 0; i < thread_count; i++)
 	 	delete dealer[i];
  	context.terminate();
	
}

// ./test <filename> start
int main(int argc, char const *argv[]){
	// arg_test(argc, argv);
	std::cout<<"Hello World, Krishna calling you.\n";
	// client_func("../zids/zid0.txt", 0 , 1);
	// zidFileRead("../zids/zid0.txt", 0 , 10);
	int start = 0;
	std::string filename = "../zids/zid0.txt";
	if (argc > 1)
	{
		std::cout<<argv[1]<<std::endl;
		filename = "../zids/"+std::string(argv[1]);
	}
	if(argc > 2){
		start = std::stoi(std::string(argv[2]));
	}
	std::cout<<"filename: "<<filename<<std::endl;
	pid_t pid = fork();
	if(0 == pid){
		// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
			pid_t pid1 = fork();
			if(0 == pid1){
				// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
				pid_t pid2 = fork();
				if(0 == pid2){
					pid_t pid3 = fork();
					if(0 == pid3){
						// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
							client_func(filename, start + 0 , start + thread_count);
					}
					else if(pid3> 0){
						pid_t pid4 = fork();
						if(0 == pid4){
							// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
								client_func(filename, start + thread_count ,start +  thread_count*2);
						}
						else if(pid4> 0){
							// std::cout<<"Parent: "<<getpid()<<"\n";
								client_func(filename, start + thread_count*2 ,start +  thread_count*3);
						}
						else{
							std::cout<<"Unable to create process\n";
						}
					}
					else{
						std::cout<<"Unable to create process\n";
					}
				}
				else if(pid2> 0){
					// std::cout<<"Parent: "<<getpid()<<"\n";
						client_func(filename, start + thread_count*3 , start + thread_count*4);
				}
				else{
					std::cout<<"Unable to create process\n";
				}
			}
			else if(pid1> 0){
				// std::cout<<"Parent: "<<pid1<<"\n";
				pid_t pid2 = fork();
				if(0 == pid2){
					pid_t pid3 = fork();
					if(0 == pid3){
						// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
							client_func(filename, start + thread_count*4 , start + thread_count*5);
					}
					else if(pid3> 0){
						// std::cout<<"Parent: "<<getpid()<<"\n";
							client_func(filename, start + thread_count*5 , start + thread_count*6);
					}
					else{
						std::cout<<"Unable to create process\n";
					}
				}
				else if(pid2> 0){
					pid_t pid3 = fork();
					if(0 == pid3){
						// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
							client_func(filename, start + thread_count*7 , start + thread_count*8);
					}
					else if(pid3> 0){
						// std::cout<<"Parent: "<<getpid()<<"\n";
							client_func(filename, start + thread_count*8 , start + thread_count*9);
					}
					else{
						std::cout<<"Unable to create process\n";
					}
				}
				else{
					std::cout<<"Unable to create process\n";
				}

			}
			else{
				std::cout<<"Unable to create process\n";
			}
	}
	else if(pid> 0){
		// std::cout<<"Parent: "<<getpid()<<"\n";
			pid_t pid1 = fork();
			if(0 == pid1){
				// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
				pid_t pid2 = fork();
				if(0 == pid2){
					pid_t pid3 = fork();
					if(0 == pid3){
						// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
							client_func(filename, start + thread_count*9 , start + thread_count*10);
					}
					else if(pid3> 0){
						// std::cout<<"Parent: "<<getpid()<<"\n";
							client_func(filename, start + thread_count*10 , start + thread_count*11);
					}
					else{
						std::cout<<"Unable to create process\n";
					}
				}
				else if(pid2> 0){
					// pid_t pid3 = fork();
					// if(0 == pid3){
					// 	// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
					// 		client_func(filename, start + thread_count*11 , start + thread_count*12);
					// }
					// else if(pid3> 0){
					// 	// std::cout<<"Parent: "<<getpid()<<"\n";
					// 		client_func(filename, start + thread_count*12 , start + thread_count*13);
					// }
					// else{
					// 	std::cout<<"Unable to create process\n";
					// }
				}
				else{
					std::cout<<"Unable to create process\n";
				}

			}
			else if(pid1> 0){
				// std::cout<<"Parent: "<<getpid()<<"\n";
				// pid_t pid2 = fork();
				// if(0 == pid2){
					// pid_t pid3 = fork();
					// if(0 == pid3){
					// 	// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
					// 		client_func(filename, thread_count*13 , thread_count*14);
					// }
					// else if(pid3> 0){
					// 	// std::cout<<"Parent: "<<getpid()<<"\n";
					// 		client_func(filename, thread_count*14 , thread_count*15);
					// }
					// else{
					// 	std::cout<<"Unable to create process\n";
					// }
				// }
				// else if(pid2> 0){
					// pid_t pid3 = fork();
					// if(0 == pid3){
					// 	// std::cout<<"Parent: "<<getppid()<<"Child:"<<getpid()<<"\n";
					// 		client_func(filename, thread_count*15 , thread_count*16);
					// }
					// else if(pid3> 0){
					// 	// std::cout<<"Parent: "<<getpid()<<"\n";
					// 		client_func(filename, thread_count*16 , thread_count*17);
					// }
					// else{
					// 	std::cout<<"Unable to create process\n";
					// }
				// }
				// else{
				// 	std::cout<<"Unable to create process\n";
				// }

			}
			else{
				std::cout<<"Unable to create process\n";
			}
	}
	else{
		std::cout<<"Unable to create process\n";
	}


	std::cout<<"exit...\n";
	return 0;
}


