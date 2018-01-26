#include <stdio.h>
/* печать таблицы температур по Фаренгейту и Цельсию для
fahr = 0, 20,..., 300; вариант с плавающей точкой */

float transform_temp(float celsius);

int main()
{
float celsius, fahr;
int lower, upper, step;
lower = 0; /* нижняя граница таблицы температур */
upper = 300; /* верхняя граница */
step = 20; /* шаг */
fahr = lower;
while (fahr <= upper) {
celsius = transform_temp(fahr);
printf("%3.0f %6.1f\n", fahr, celsius);
fahr = fahr + step;
}
return 0;
}

float transform_temp(float fahr)
{
float celsius;
celsius = (5.0/9.0) * (fahr-32.0);
return celsius;
}
