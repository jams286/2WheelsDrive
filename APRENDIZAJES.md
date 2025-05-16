# Notas Técnicas y Aprendizajes

## 🔧 Problemas enfrentados

* **PWM con ESP32:** El comando `analogWrite()` no está disponible en ESP32. Se reemplazó por `ledcWrite()` junto con la configuración de canales y resolución PWM.

* **Giros invertidos al avanzar:** Al intentar girar mientras el robot avanzaba, el movimiento era contrario al esperado. Se implementó lógica condicional para distinguir entre giro estático (detenido) y giro suave (en marcha).

* **PWM de 3.3V desde ESP32:** El L298N funciona correctamente con señales de 3.3V provenientes del ESP32, aunque se recomienda verificar compatibilidad para otros drivers.
* **Alimentacion del sistema:** Al conectar el ESP32 junto al L298N y los motores a la misma fuente de alimentacion (4 Baterias de 1.3v) los motores dejaban de funcionar debido a la falta de corriente, por lo que se optó por agregar un powerbank para alimentar el ESP32 y el L298N y dejar las baterias exclusivamente para los motores.

## 🧠 Decisiones de diseño

* **Chasis 2WD:** Se eligió un diseño de dos ruedas motrices por su simplicidad mecánica, eficiencia energética y buena maniobrabilidad en interiores.

* **Uso de control PS4:** Se optó por el control PS4 por su buena ergonomía, conectividad Bluetooth confiable con ESP32 y soporte de librerías como `PS4Controller`.

* **Driver L298N:** Aunque existen opciones más eficientes, se usó el L298N por disponibilidad, documentación y compatibilidad con los motores utilizados.

* **Joystick izquierdo para velocidad, derecho para giro:** Esta configuración ofrece un control intuitivo tipo "tanque" adaptado al comportamiento esperado por el usuario.

## 🚀 Mejoras futuras

* Mejoras en el chasis.
* Para una futura versión se consideraría una batería LiPo con mayor salida de corriente.
* Mejoras en codigo para casos donde se pierde la conexion con el control.
* Cambiar a un driver más eficiente como el TB6612FNG para reducir pérdida de potencia y temperatura.
* Agregar sensores ultrasónicos o de proximidad para detección de obstáculos.
* Implementar una app móvil o interfaz web para control vía WiFi.
* Incorporar retroalimentación de velocidad con encoders para control más preciso.

## 📈 Reflexión final

Este proyecto sirvió como base para probar integración de hardware (motores, ESP32, driver) y software (PS4, Bluetooth, PWM). También sentó las bases para proyectos futuros más complejos como robots seguidores de línea, balancers o autónomos.
