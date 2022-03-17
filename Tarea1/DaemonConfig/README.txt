When the daemon service is ready you need to notify the systemd with:
	sudo cp ImageServerDaemon.service /lib/systemd/system

	sudo systemctl daemon-reload
	sudo systemctl enable ImageServerDaemon

en el servicio normalmente el path inicia con /bin/..
pero como no tenemos la carpeta supongo que es mejor con /urs/
