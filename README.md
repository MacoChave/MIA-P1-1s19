# Manejo e Implementación de Archivos
## Proyecto 1 - Primera Fase

Interprete de comandos por consola para el **CRUD** de particiones en discos duros virtuales (archivos `.disk | .dsk`) modificando las particiones primarias, extendidas y lógicas.

### Comandos
* **`exit`** : Cierra la aplicación.
* **`mkdisk`** : Crea un disco.
* **`rmdisk`** : Eliminar disco.
* **`fdisk`** : Crear o modifica particiones primarias, extendidas o lógicas.
* **`mount`** : Monta la partición de un disco para su uso en el sistema.
* **`rep`** : Crea reportes tanto de la estructura del mbr y ebr como del estado del disco.

#### mkdisk
Los parámetros que reconoce son los siguientes:
* `path` : Es una propiedad obligatoria. Define la ruta en la que se creará el disco.
* `size` : Es una propiedad obligatoria. Define el tamaño que tendrá el disco.
* `fit` : Define el tipo de ajuste que se utilizará al crear una partición.
* `unit` : Define la unidad de medida que se multiplicará el tamaño del disco para su creación.

#### rmdisk
* `path` : Es una propiedad obligatoria. Define la ruta en la que se encuentra el disco a eliminar.

#### fdisk
* `size` : Define el tamaño que tendrá la partición.
* `unit` : Define la unidad de medida que se multiplicará el tamaño de la partición.
* `path` : Es una propiedad obligatoria. Define la ruta del disco a crear la partición.
* `type` : Define el tipo de partición a crear.
* `fit` : Define el tipo de ajuste que se utilizará al crear una partición.
* `name` : Es una propiedad obligatoria. Es el nombre que se le dará a la partición a crear ó el nombre de la partición a eliminar.
* `delete` : Solo se tomará cuando se quiera eliminar una partición.
* `add` : Solo se tomará cuando se quiera modificar el tamaño de la partición, ya sea para reducir (número negativo) o aumentar (número positivo).

#### mount
* `path` : Es una propiedad obligatoria e indica la dirección donde se encuentra el disco duro del cual se desea la partición.
* `name` : Es una propiedad obligatoria e indica el nombre de la partición a montar.

#### rep
* `id` : Es una propiedad obligatoria y nos indica el nombre de la partición montada a obtener los reportes. Dicho id viene compuesto con el patrón: vd[letra disco][numero partición].
* `path` : Es una propiedad obligatoria y nos dice la ruta donde se exportará el reporte.
* `name` : Es una propiedad obligatoria y nos indica que tipo de reporte exportar. Ya sea **_disk_** para un esquema del estado del disco ó **_mbr_** para los cuadros de la estructura del disco.