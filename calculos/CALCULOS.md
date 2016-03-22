# Cálculos

Estos son los calculos que se utilizan en el sketch para convertir los valores analógicos de los sensores.


### Alcohol

**Puntos de la curva**

Rs/Ro | mg/L
------------ | -------------
0,1333 | 10
0,16666 | 8
0,17 | 6
0,18 | 4
0,19 | 2,5
0,2 | 1,8
0,23 | 1,4
0,6 | 0,9
0,7 | 0,7
0,8 | 0,6
0,9 | 0,5
1 | 0,4
1,66666 | 0,21
1,24 | 0,1

**Ecuación potencial**

- Expresión:
```
y = 0,337x-1,45 
```
- Código:
```arduino
double Alcohol = 0.337*pow(mq3_resistencia/5463, -1.45);
```