# EJECUTA EL SCRIPT
# exec -path~:~ejemplos/entrada1.sh

#Crea un disco de 3000 Kb en la carpeta home
Mkdisk -Size~:~3000 -unit~:~K -path~:~/home/user/Disco1.dsk
#No es necesario utilizar comillas para la ruta en este caso
Mkdisk -path~:~/home/user/Disco2.dsk -Unit~:~K -size~:~3000
#Se ponen comillas por la carpeta “mis discos”, se crea si no está
mkdisk -size~:~5 -unit~:~M -path~:~"/home/mis discos/Disco3.dsk"
#Creará un disco de 10 Mb ya que no hay parámetro -unit~:~ 
mkdisk -size~:~10 -path~:~"/home/mis discos/Disco4.dsk"

#Elimina Disco4.dsk
rmDisk -path~:~"/home/mis discos/Disco4.dsk"

#Crea una partición primaria llamada Particion1 de 300 kb
#con el peor ajuste en el disco Disco1.dsk
fdisk -Size~:~300 -path~:~/home/Disco1.dsk -name~:~Particion1
#Crea una partición extendida dentro de Disco2 de 300 kb
#Tiene el peor ajuste
fdisk -type~:~E -path~:~/home/Disco2.dsk -Unit~:~K -name~:~Particion2 -size~:~300
#Crea una partición lógica con el mejor ajuste, llamada Paricion3,
#de 1 Mb en el Disco3
fdisk -size~:~1 -type~:~L -unit~:~M -fit~:~BF -path~:~"/mis discos/Disco3.dsk" -name~:~"Particion3"
#Intenta crear una partición extendida dentro de Disco2 de 200 kb
#Debería mostrar error ya que ya existe una partición extendida
#dentro de Disco2
fdisk -type~:~E -path~:~/home/Disco2.dsk -name~:~Part3 -Unit~:~K -size~:~200

#Elimina de forma rápida una partición llamada Particion1
fdisk -delete~:~fast -name~:~"Particion1" -path~:~/home/Disco1.dsk
#Elimina de forma completa una partición llamada Particion1
fdisk -name~:~Particion1 -delete~:~full -path~:~/home/Disco1.dsk
#Quitan 500 Kb de Particion4 en Disco4.dsk
#Ignora los demás parametros -size~:~ -delete~:~
#Se toma como válido el primero que aparezca, en este caso-add
fdisk -add~:~-500 -size~:~10 -unit~:~K -path~:~"/home/misdiscos/Disco4.dsk" -name~:~"Particion4"
#Agrega 1 Mb a la partición Particion4 del Disco4.dsk #Se debe validar que
#haya espacio libre después de la partición
fdisk -add~:~ -unit~:~M -path~:~"/home/mis discos/Disco4.dsk" -name~:~"Particion 4"

#Monta las particiones de Disco1.dsk
mount -path~:~/home/Disco1.dsk -name~:~Part1  #id=vda1
mount -path~:~/home/Disco2.dsk -name~:~Part1  #id=vdb1
mount -path~:~/home/Disco3.dsk -name~:~Part2  #id=vdc1
mount -path~:~/home/Disco1.dsk -name~:~Part2  #id=vda2

#Desmonta la partición con id vda1 (En Disco1.dsk)
unmount -id~:~vda1
#Si no existe, se debe mostrar error
unmount -id~:~vdx1

rep -id~:~vda1 -Path~:~/home/user/reports/reporte1.jpg -name~:~mbr
rep -id~:~vda2 -Path~:~/home/user/reports/reporte2.pdf -name~:~disk