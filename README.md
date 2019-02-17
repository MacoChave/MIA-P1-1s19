# Manejo e Implementación de Archivos
## Proyecto 1 - Primera Fase

Interprete de comandos por consola para el **CRUD** de particiones en discos duros virtuales (archivos `.disk | .dsk`) modificando las particiones primarias, extendidas y lógicas.

### Comandos
* **`exit`** : Cierra la aplicación.
* **`mkdisk`** : Crea un disco.
* **`rmdisk`** : Eliminar disco.
* **`fdisk`** : Crear o modifica particiones primarias, extendidas o lógicas.

#### mkdisk
Los parámetros que reconoce son los siguientes:
* `path` : Define la ruta en la que se creará el disco.
* `size` : Define el tamaño que tendrá el disco.
* `fit` : Define el tipo de ajuste que se utilizará al crear una partición.
* `unit` : Define la unidad de medida que se multiplicará el tamaño del disco para su creación.

#### rmdisk
* `path` : Define la ruta en la que se encuentra el disco a eliminar.

#### fdisk
* `size` : Define el tamaño que tendrá la partición.
* `unit` : Define la unidad de medida que se multiplicará el tamaño de la partición.
* `path` : Define la ruta del disco a crear la partición.
* `type` : Define el tipo de partición a crear.
* `fit` : Define el tipo de ajuste que se utilizará al crear una partición.
* `name` : Es el nombre que se le dará a la partición a crear ó el nombre de la partición a eliminar.
* `delete` : Solo se tomará cuando se quiera eliminar una partición.
* `add` : Solo se tomará cuando se quiera modificar el tamaño de la partición, ya sea para reducir (número negativo) o aumentar (número positivo).