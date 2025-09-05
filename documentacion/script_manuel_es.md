# script(1)

## NOMBRE
`script` - crea un registro (typescript) de la sesión del terminal.

---

## SINOPSIS
`script` [opciones] [archivo]

---

## DESCRIPCIÓN
`script` crea un registro de todo lo que ocurre en tu sesión de terminal. Los datos del terminal se almacenan en bruto en un archivo de registro y la información de tiempos en otro archivo de registro estructurado (opcional). El archivo de registro de tiempos es necesario para reproducir la sesión más tarde mediante `scriptreplay(1)` y para almacenar información adicional sobre la sesión.

A partir de la versión 2.35, `script` soporta múltiples flujos y permite registrar la entrada y la salida en archivos separados o en un solo archivo. Esta versión también soporta un nuevo archivo de tiempos que registra información adicional. El comando `scriptreplay --summary` proporciona toda esta información.

Si se proporciona el argumento `archivo` o la opción `--log-out archivo`, `script` guarda el diálogo en ese archivo. Si no se da ningún nombre de archivo, el diálogo se guarda en el archivo **typescript**.

**Nota**: registrar la entrada usando `--log-in` o `--log-io` puede almacenar información sensible a la seguridad, ya que el archivo de registro contiene toda la entrada de la sesión del terminal (por ejemplo, contraseñas) independientemente de la configuración de eco del terminal.

---

## OPCIONES
- **`-a, --append`**
  Añade la salida al archivo o al `typescript`, conservando el contenido previo.
- **`-c, --command comando`**
  Ejecuta el comando en lugar de un shell interactivo.
- **`-E, --echo cuando`**
  Controla la bandera `ECHO` para el extremo esclavo del pseudoterminal de la sesión. Los modos soportados son `always`, `never` o `auto`.
- **`-e, --return`**
  Devuelve el estado de salida del proceso hijo.
- **`-f, --flush`**
  Vacía la salida después de cada escritura.
- **`--force`**
  Permite que el archivo de salida por defecto `typescript` sea un enlace físico o simbólico.
- **`-B, --log-io archivo`**
  Registra entrada y salida en el mismo archivo.
- **`-I, --log-in archivo`**
  Registra la entrada en el archivo.
- **`-O, --log-out archivo`**
  Registra la salida en el archivo. Por defecto, es `typescript`.
- **`-T, --log-timing archivo`**
  Registra información de tiempos en el archivo.
- **`-m, --logging-format formato`**
  Fuerza el formato de registro (`clásico` o `avanzado`).
- **`-o, --output-limit tamaño`**
  Limita el tamaño de los archivos de registro.
- **`-q, --quiet`**
  Modo silencioso (no muestra mensajes de inicio y fin).
- **`-t[archivo], --timing[=archivo]`**
  Envía datos de tiempos a `stderr`, o a un archivo si se especifica. **(Obsoleta)**
- **`-V, --version`**
  Muestra la versión y sale.
- **`-h, --help`**
  Muestra la ayuda y sale.

---

## SEÑALES
Al recibir `SIGUSR1`, `script` vacía inmediatamente los archivos de salida.

---

## ENTORNO
- **`SHELL`**
  Si existe, `script` usa esa shell. Si no, se asume `sh`.

---

## NOTAS
`script` termina cuando la shell creada sale (por ejemplo, con `Ctrl+D`).

Algunos comandos interactivos como `vi` pueden generar basura en el registro. `script` funciona mejor con comandos que no manipulan la pantalla.

Evita usar `script` en pipes o en shells no interactivas, ya que puede generar resultados inesperados o colgarse.

---

## ERRORES
- `script` registra todo, incluyendo saltos de línea y retrocesos, lo que puede ser confuso.
- No es adecuado para usar en pipes si la entrada no es un terminal interactivo, ya que puede colgarse.