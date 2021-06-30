# Testeo del programa

## ¿Cómo están armados los tests?
Cada prueba X consta de 3 archivos:

+ `Xprop.md`: explica brevemente el propósito de la prueba

+ `Xtest.txt`: contiene la entrada proporcionada al programa

+ `Xtestrdo.txt`: contiene la salida del programa

Además se cuenta con una carpeta titulada archivos en donde se encuentran los archivos utilizados para la carga y guardado dentro del programa.

## ¿Cómo verificar los tests?
Los archivos de resultado se obtuvieron corriendo 

    cat pathToTest/testX.txt | ./main > pathToTestRdo/rdotestX.txt

se puede verificar que estos son correctos volviendo a correr el mismo comando.




