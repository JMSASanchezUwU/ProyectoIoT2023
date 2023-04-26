# ProyectoIoT2023
GDS0453 - Documentación proyecto IoT 

## Integrantes
- Brandon Jesús Soto Rangel
- José Manuel Sánchez Arredondo
- Victor Javier Otero

## Objetivo general
El objetivo en general de nuestro proyecto es proteger espacios que no estan seguros o son propensos a se inseguros, por lo que proponemos
nuestro proyecto para hacer seguras de esas zonas a las que propensa la inseguridad de algun espacio.
### Objetivos específicos
- 1.- Planeación de prototipo.
- 2.- Diseñado del prototipo.
- 3.- Validación de prototipo.
- 4.- Test de prototipo.
- 5.- Realización de proyecto final.
- 6.- Test de proyecto.
- 7.-Liberación de proyecto.

## Tabla de Software utilizado
| Id | Software | Version | Tipo |
|----|----------|---------|------|
|1.1|Arduino IDE | 2-0.4 |Freeware|
|1.2|Visual Studio Code | 1.74.3 |Freeware|
|1.3|Mosquitto   | 5.0.3.1.1|Freeware|
|1.4|Node-Red   | 3.0.2 |Freeware|
|1.5|Node.js  | 18.13.0 |Freeware|
|1.6|Maria DB | 10.3 |Freeware|
|1.7|Telegram | 9.6.1 |Freeware|

## Tabla con el hardware utilizado
| Id | Componente | Descripción | Imagen | Cantidad | Costo total |
|----|------------|-------------|--------|----------|-------------|
|2.1|  Esp32  | Es la denominación de una familia de chips SoC de bajo coste y consumo de energía, con tecnología Wi-Fi y Bluetooth de modo dual integrada.            |![image](https://user-images.githubusercontent.com/106613839/217649811-9335a9c7-5a4c-4813-8f17-e03488f52967.png)| 1         | $150            |
|2.2|  Cables          | Clabes por los cuales se harán conecciones entre sensores, actuadores y la esp32|![image](https://user-images.githubusercontent.com/106613839/217650692-88574d94-022c-44fe-a183-58dd5121c26a.png)| 20         |  $80           |
|2.3| Foco con socket  | Foco el cual será controlado para iluminar una zona.   |![image](https://user-images.githubusercontent.com/106613839/217650095-d221a148-1c63-45fc-8211-0f1e97fa8816.png)| 1    | $80            |
|2.4| Sensor PIR  | Es un dispositivo de deteccion de presencia. |![image](https://user-images.githubusercontent.com/106613839/217650180-a6823830-87e4-4c25-aaa7-666262828d59.png)| 1   |  $70           |
|2.5| Modulo Relay  | Es un dispositivo que funciona como un interruptor controlado por un circuito eléctrico. |![image](https://user-images.githubusercontent.com/106613839/217650285-e2eb47d3-dd0d-417d-8b56-bc9ed793780a.png)| 1 | $100  |
|2.6| Raspberry Pi  | Consiste en una placa base que soporta distintos componentes de un ordenador como un procesador ARM de hasta 1500 MHz, un chip gráfico y una memoria RAM de hasta 8 GB. Además, tiene otras muchas otras posibilidades. Gracias a sus puertos y entradas, permite conectar dispositivos periféricos. |![image](https://user-images.githubusercontent.com/106613839/217650399-cdfdb686-4b04-4740-9ed4-f50115d25a98.png)|  1        | $2750            |
|2.7| Buzzer  | Es un pequeño duspositivo capaz de convertir energía eléctrica en sonido. |![image](https://user-images.githubusercontent.com/106613839/217650467-74e67b77-a1b1-4a00-9268-57ff7921a149.png)|  1   | $20   |
|2.8| Botón  | Solo un sencillo botón. |![image](https://user-images.githubusercontent.com/106613839/233920323-8ebc0cce-451c-405e-8347-b46cbf8722b1.png)| 1 | $10 |
|2.9| MQ-2  | Sensor que detecta humo y gas.|![image](https://user-images.githubusercontent.com/106613839/233920671-4e8d8db1-8f5b-4ed4-85db-b6a6f2bd4ed5.png)| 1 | $75 |
|2.10| Display OLED  | Pantalla con tecnología OLED que emite luz propia y nítida. |![image](https://user-images.githubusercontent.com/106613839/233921614-5501b5f8-bc25-4e67-9ae6-b3f3069594ad.png)| 1 | $95 |
|2.11| Placa fenólica | Placa hecha de papel impregnado con resina fenólica endurecida. Es un circuito impreso. |![image](https://user-images.githubusercontent.com/106613839/233930710-8fb3ca33-d93f-4d8d-ac8f-adf434ff0cbd.png)| 1 | $22 |


## Epicas del proyecto (Minimo debe de haber una épica por integrante de equipo)
- Yo como usuario quiero detectar personas o algunas otras entidades agenas a un cierto espacio.
- Yo como usuario quiero iluminar la zona detectada con precencia de otras ajenas a un cierto espacio.
- Yo como usuario quiero que el dispositivo lance una alarma la cual avise si se detecto un movimiento.
- Yo como usuario quiero poder almacenar informción de las detecciones que se dieron en cada activación de del dispositivo.
- Yo como usuario quiero poder consultar las detecciones que se dieron en cada activación del dispositivo a traves de telegram.
- Yo como usuario quiero saber la humedad y temperatura de un cierto espacio.

## Tabla de historias de usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
|3.1 | Yo como usuario quiero detectar personas o algunas otras entidades agenas a un cierto espacio. | Alta | 3 Meses  | Pasar frente al dispositivo y revisar el celular si llego alguna notificacion de la app.| Brandon y José Manuel |
| 3.2 | Yo como usuario quiero iluminar la zona detectada con precencia de otras ajenas a un cierto espacio. | Alta | 3 Meses | Pasar frente al dispositivo y ver si enciende el foco.| Brandon y José Manuel |
| 3.3 | Yo como usuario quiero que el dispositivo lance una alarma la cual avise si se detecto un movimiento. | Alta | 1 Mes | Pasar frente al dispositivo y ver si emite un sonido.| Brandon |
| 3.4 | Yo como usuario quiero poder almacenar informción de las detecciones que se dieron en cada activación de del dispositivo. | Semi-Alta | 1 Mes | Checar en el dispositivo el registro de las detecciones.  | José Manuel |
| 3.5 | Yo como usuario quiero poder consultar las detecciones que se dieron en cada activación del dispositivo. | Semi-Alta | 1 Mes | A través de un dispositivo móvil | Brandon |
| 3.6 |  Yo como usuario quiero saber la humedad y temperatura de un cierto espacio. | Semi-Alta | 2 semanas | A través de un dispositivo móvil | José Manuel |

## Prototipo en dibujo
- Coloca la fotografia de tu prototipo dibujado a lapiz
![image](https://user-images.githubusercontent.com/106613839/233937328-e5c8ec09-7483-45c5-b03a-d755075017e8.png)
## Demostración Video
https://vm.tiktok.com/ZMY3j8khT/

