### 📂 Funciones de Gestión de Archivos y Descriptores

Estas funciones permiten a tu programa interactuar con el sistema de archivos del sistema operativo.

* **`read`**
    * **Prototipo**: `ssize_t read(int fildes, void *buf, size_t nbyte);`
    * **¿Qué hace?**: Lee hasta `nbyte` bytes del archivo asociado al descriptor de archivo `fildes` y los almacena en el búfer `buf`.
    * **Parámetros**:
        * `fildes`: El descriptor de archivo de donde se va a leer.
        * `buf`: Un puntero al búfer donde se guardarán los datos.
        * `nbyte`: La cantidad máxima de bytes a leer.

* **`write`**
    * **Prototipo**: `ssize_t write(int fildes, const void *buf, size_t nbyte);`
    * **¿Qué hace?**: Escribe hasta `nbyte` bytes del búfer `buf` en el archivo asociado al descriptor de archivo `fildes`.
    * **Parámetros**:
        * `fildes`: El descriptor de archivo donde se va a escribir.
        * `buf`: Un puntero al búfer que contiene los datos a escribir.
        * `nbyte`: La cantidad de bytes que se van a escribir.

* **`open`**
    * **Prototipo**: `int open(const char *path, int oflag, ...);`
    * **¿Qué hace?**: Abre un archivo y devuelve un nuevo descriptor de archivo.
    * **Parámetros**:
        * `path`: La ruta al archivo.
        * `oflag`: Banderas que controlan el modo de apertura (`O_RDONLY`, `O_WRONLY`, `O_RDWR`, etc.).
        * `...`: El tercer parámetro, si se usa la bandera `O_CREAT`, debe ser un `mode_t` para los permisos del archivo.

* **`close`**
    * **Prototipo**: `int close(int fildes);`
    * **¿Qué hace?**: Cierra un descriptor de archivo, liberando los recursos del sistema asociados.
    * **Parámetros**:
        * `fildes`: El descriptor de archivo que se quiere cerrar.

---

### 🧠 Funciones de Gestión de Memoria

Estas funciones te permiten gestionar la memoria de tu programa a bajo nivel.

* **`sbrk`**
    * **Prototipo**: `void *sbrk(intptr_t increment);`
    * **¿Qué hace?**: Aumenta o disminuye el tamaño del segmento de datos del programa.
    * **Parámetros**:
        * `increment`: El número de bytes en que se va a aumentar (si es positivo) o disminuir (si es negativo) el segmento.

* **`brk`**
    * **Prototipo**: `int brk(void *addr);`
    * **¿Qué hace?**: Establece el nuevo final del segmento de datos en una dirección de memoria específica.
    * **Parámetros**:
        * `addr`: La nueva dirección de memoria para el final del segmento de datos.

---

### ⚙️ Funciones de Gestión de Procesos

Estas funciones te permiten crear, controlar y terminar procesos.

* **`fork`**
    * **Prototipo**: `pid_t fork(void);`
    * **¿Qué hace?**: Crea un nuevo proceso hijo que es una copia del proceso padre.
    * **Parámetros**: Ninguno.

* **`exit`**
    * **Prototipo**: `void exit(int status);`
    * **¿Qué hace?**: Termina la ejecución del proceso actual y devuelve un código de estado.
    * **Parámetros**:
        * `status`: El código de estado que se devuelve al proceso padre.

* **`execve`**
    * **Prototipo**: `int execve(const char *path, char *const argv[], char *const envp[]);`
    * **¿Qué hace?**: Reemplaza el programa actual con uno nuevo, conservando el mismo ID de proceso.
    * **Parámetros**:
        * `path`: La ruta al nuevo programa ejecutable.
        * `argv`: Un array de argumentos para el nuevo programa.
        * `envp`: Un array de variables de entorno para el nuevo programa.

---

### 🕰️ Funciones de Reloj y Tiempo

Estas funciones te permiten obtener información sobre el tiempo del sistema.

* **`time`**
    * **Prototipo**: `time_t time(time_t *tloc);`
    * **¿Qué hace?**: Devuelve la hora actual del sistema en segundos desde el 1 de enero de 1970.
    * **Parámetros**:
        * `tloc`: Un puntero a una variable `time_t` donde se guardará el valor, o `NULL`.

---

### 📜 La Excepción Permitida

* **`ctime`**
    * **Prototipo**: `char *ctime(const time_t *timep);`
    * **¿Qué hace?**: Convierte un valor de tiempo en una cadena de caracteres legible que representa la fecha y la hora.
    * **Parámetros**:
        * `timep`: Un puntero a una variable `time_t` que contiene el tiempo a convertir.