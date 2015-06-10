all:
	gcc -o client rfcomm-client.c -lbluetooth
	gcc -o server rfcomm-server.c -lbluetooth
	g++ -o scan simplescan.cpp scan.cpp -lbluetooth
