#!/bin/bash

#enter
#echo "-n" "\n"

#sprawdzanie czy istnieje plik na dane na temat przebiegu skryptu.
#Jeżeli nie, to zostaje taki tworzony
if [ -a ./temp ]
then
	read stage < ./temp
else
	sudo touch temp
	sudo echo "0" | sudo tee temp > /dev/null
	read stage < ./temp
fi

#sudo nano /boot/cmdline.txt
#skasuj console=serial0,115200

#dodać dłuższa sumę crc

#zeby uruchomic UART dodalem do pliku config.txt 
#znajdujacego sie w /boot/
#linijke 
#...
#dtoverlay=pi3-disable-bt
#...
#i zrebootowac potem


case "$stage" in

	"0")

		#dodawanie skryptu do autostartu
		sudo echo "sudo /home/pi/setup-handless.sh" | sudo tee -a /etc/profile > /dev/null
		sudo echo "1" | sudo tee temp > /dev/null ;&

	"1")

		#usuwa logowanie na początku uruchomienia systemu
		sudo ln -fs /etc/systemd/system/autologin@.service /etc/systemd/system/getty.target.wants/getty@tty1.service
		sudo echo "2" | sudo tee temp > /dev/null ;&

	"2")

		#zmiana ukladu klawiatury
		sudo sed -i 's/"gb"/"pl"/' /etc/default/keyboard

		#zapis postepow
		sudo echo "3" | sudo tee temp > /dev/null ;&

	"3")
		
		#

		#prospa o podanie hasla do sieci i ustawienie go w pliku
		sudo wpa_passphrase HTC "12345678" | sudo tee -a /etc/wpa_supplicant/wpa_supplicant.conf > /dev/null

		#usuniecie jawnego hasla do sieci
		sudo sed -i '/#psk=/d' /etc/wpa_supplicant/wpa_supplicant.conf

		#polaczenie z nowo dodana siecia
		sudo wpa_cli -i wlan0 reconfigure

		#czekanie na polaczenie z sieciak
		sudo sleep 10s

		#zapis postepow
		sudo echo "4" | sudo tee temp > /dev/null ;&

	"4")

		#aktualizacja systemu
		sudo apt-get update -y
		sudo apt-get upgrade -y

		#zapis postepow
		sudo echo "5" | sudo tee temp > /dev/null ;&
		#sudo reboot now ;&

	"5")
	
		#uruchomienie ssh
		sudo systemctl enable ssh
		sudo systemctl start ssh
		sudo echo "6" | sudo tee temp > /dev/null ;&

	"6")

		#dodawanie skryptu do autostartu
		sudo echo "dtoverlay=pi3-disable-bt" | sudo tee -a /boot/config.txt > /dev/null
		sudo echo "7" | sudo tee temp > /dev/null ;&
		
	"7")

		#usuniecie pliku z autostartu oraz pliku temp
		sudo sed -i '/setup-handless.sh/d' /etc/profile
		sudo rm -rf temp ;;

esac