# TA2
Program TA2

# Spesifikasi Alat:
1.  Sensor PIR HC-SR501 
![Image](https://www.elektor.com/media/catalog/product/cache/2b4bee73c90e4689bbc4ca8391937af9/a/x/axirissensorc-web.jpg)
2.	Mikrokontroler NodeMCU ESP8266 
![Image](https://images-na.ssl-images-amazon.com/images/I/81U4jvpGnYL._SL1500_.jpg)
3.  NodeMCU Base ![Image](https://i.ebayimg.com/00/s/MTAwMFgxMDAw/z/Ea4AAOSw-4Fdif5G/$_10.JPG?set_id=880000500F)
4.	Relay NC ![Image](https://robu.in/wp-content/uploads/2017/06/2-Channel-Relay-Module11.jpg)
5.	Kabel jumper male to male
6.	Kabel jumper male to female
7.	Bohlam lampu
8.	Fitting lampu
9.	Breadboard
10.	Kabel listrik
11.	Steker listrik

# Aplikasi
Pembuatan aplikasi pake MIT App Inventor

# Database
Pembuatan DB pake Firebase

# Alat yang sementara dikerjakan:
1.  Sensor PIR HC-SR501  
2.	Mikrokontroler NodeMCU
3.	Relay
4.  NodeMCU Base

# Logic
1. Ketika terdeteksi gerakan pada satu sensor, maka sensor di sebelahnya set on, selain itu set off
2. Jika sensor = root maka abaikan perintah sensor lain
3. Ketika ada lampu di tetangga sedang on maka nyalakan sensor
4. Ketika masih mendeteksi orang di sensor maka device mengabaikan perintah
5. Jika mode manual bukan -1 maka set lampu sesuai user command