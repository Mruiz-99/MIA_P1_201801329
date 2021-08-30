# Manejo e implemetancion de archivos      <img src="./imagenes/usac_escudo.png" alt="" width="100"/>
--------
-------
## Sistema de archivos ##

Es una aplicación en consola desarrollada en c/c++ que simula los sistemas de archivos EXT2 y EXT3. Este sistema no tiene menus, sino que se utilizaran comandos(scripts) para su manipulación. 

-------- 
--------

## Objetivos ##
- Administrar archivos y escribir estructuras en C/C++
- Comprender el sistema de archivos EXT3 y EXT2
- Aplicar el formateo rápido y completo en una partición
- Aplicar la teoría de ajustes
- Aplicar la teoría de particiones
- Utilizar GraphViz para mostrar reportes
- Restringir y administrar el acceso a los archivos y carpetas en ext3/ext2 por medio de usuarios
- Administrar los usuarios y permisos por medio de grupo

-----
-----

## Comandos ##
-------
------


### Administración de discos

#### Descripcion:
- MKDISK: Crea un archivo binario, simulando un disco duro 
#### Parametros:
![image info](/imagenes/mkdisk1.png)
![image info](imagenes//mkdisk2.png)

------
#### Descripcion:
-  RMKDISK: Borra el archivo que simula el disco duro.
#### Parametros:
![image info](/imagenes/rmdisk1.png)

------
#### Descripcion:
- FDISK: Administrara las operaciones que se hagan en una particion como crear, eliminar o quitar espacio.
#### Parametros:
![image info](/imagenes/fdisk1.png)
![image info](/imagenes/fdisk2.png)
![image info](/imagenes/fdisk3.png)

-----
#### Descripcion:
- MOUNT: Montara una particion en memoria
#### Parametros:
![image info](/imagenes/mount1.png)

-----
#### Descripcion:
- UNMOUNT: Desmontara una particion en memoria
#### Parametros:
![image info](/imagenes/mount1.png)

------
#### Descripcion:
- MKFS: Realiza un formateo completo de la partición, podrá ser ext2 o ext3 y crea un archivo llamado users.txt que tendrá los usuarios y contraseñas del sistema de archivos. 
 #### Parametros:
![image info](/imagenes/mkfs1.png)
![image info](/imagenes/mkfs2.png)

-----
 
 ### Administración de usuarios y grupos
#### Descripcion:
- LOGIN: Se utiliza para iniciar sesión en el sistema
-  #### Parametros:
![image info](/imagenes/login1.png)

------
#### Descripcion:
- LOGOUT: Se utiliza para cerrar sesión
 #### Parametros:
Este comando no recibe ningun parametro

----- 
#### Descripcion:
- MKGRP: Crea un grupo para los usuarios de la partición y se guarda en el archivo users.txt de la partición
-  #### Parametros:
![image info](/imagenes/mkgrp1.png)

---- 
#### Descripcion:
- RMGRP: Elimina un grupo para los usuarios de la partición
-  #### Parametros:
![image info](/imagenes/rmgrp1.png)

----- 
#### Descripcion:
- MKUSR: Crea un usuario en la partición
-  #### Parametros:
![image info](/imagenes/mkusr1.png)

-----
#### Descripcion:
- RMUSR: Elimina un usuario en la partición
-  #### Parametros:
![image info](/imagenes/rmusr1.png)
 
------

### Administración de carpetas, archivos y permisos
#### Descripcion:
- CHMOD: Cambia los permisos de un archivo o carpeta dentro del sistema de archivos
-  #### Parametros:
![image info](/imagenes/chmod1.png)
![image info](/imagenes/chmod2.png)
![image info](/imagenes/chmod3.png)
 
------ 
#### Descripcion:
- TOUCH: Crea un archivo y el propietario será el usuario que actualmente ha iniciado  sesión. Tendrá los permisos 664.
-  #### Parametros:
![image info](/imagenes/touch1.png)
![image info](/imagenes/touch2.png)
![image info](/imagenes/touch3.png)
  
------
#### Descripcion:
- CAT: Permite mostrar el contenido de un archivo, si el usuario que actualmente está logueado tiene acceso al permiso de lectura.
-  #### Parametros:
![image info](/imagenes/cat1.png)
 
----- 
#### Descripcion:
- RM: Elimina un archivo o carpeta y todo su contenido
-  #### Parametros:
![image info](/imagenes/rm1.png)

------
#### Descripcion:
- EDIT: Permite editar el contenido de un archivo para asignarle otro contenido
-  #### Parametros:
![image info](/imagenes/edit1.png)
![image info](/imagenes/edit2.png)

-----
#### Descripcion:
- REN: Cambia el nombre de un archivo o carpeta
-  #### Parametros:
![image info](/imagenes/ren1.png)
![image info](/imagenes/ren2.png)

-----
#### Descripcion:
- MKDIR: Crea una carpeta y el propietario será el usuario que actualmente ha iniciado  sesión. Tendrá los permisos 664.
-  #### Parametros:
![image info](/imagenes/mkdir1.png)
![image info](/imagenes/mkdir2.png)

-----
#### Descripcion:
- CP: Realiza una copia del archivo o carpeta y todo su contenido hacia otro destino
-  #### Parametros:
![image info](/imagenes/cp1.png)
![image info](/imagenes/cp2.png)

-----
#### Descripcion:
- MV: Mueve un archivo o carpeta y todo su contenido hacia otro destino
-  #### Parametros:
![image info](/imagenes/mv1.png)

-----
#### Descripcion:
- FIND: Realiza una búsqueda por el nombre del archivo o carpeta
-  #### Parametros:
![image info](/imagenes/find1.png)

-----
#### Descripcion:
- CHOWN: Cambia el propietario de uno o varios archivos o carpetas
-  #### Parametros:
![image info](/imagenes/chown1.png)
![image info](/imagenes/chown2.png)

-----
#### Descripcion:
- CHGRP: Cambia el grupo al que pertenece el usuario
-  #### Parametros:
![image info](/imagenes/chgrp1.png)
![image info](/imagenes/chgrp2.png)

-----
#### Descripcion:
- PAUSE: Ejecutara un archivo con comandos ya escritos.
 #### Parametros:
Este comando no recibe ningun parametro

------------
#### Descripcion:
- REP: Generara un reporte tipo imagen
 -  #### Parametros:
![image info](/imagenes/rep1.png)
![image info](/imagenes/rep2.png)

-----
#### Descripcion:
- EXEC: Ejecutara un archivo con comandos ya escritos.
- -  #### Parametros:
![image info](/imagenes/exec1.png)
