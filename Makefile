all:
	gcc -o client rfcomm-client.c -lbluetooth
	gcc -o server rfcomm-server.c -lbluetooth
	gcc -o scan simplescan.c -lbluetooth
