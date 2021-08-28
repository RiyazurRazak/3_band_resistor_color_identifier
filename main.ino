//3 band resistor color code identifier
//author : riyazurrazak

#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {12, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

double value = 0.0;
String res_val = "";
int flag = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
}

void loop()
{
    char customKey = customKeypad.getKey();

    if (customKey == 'D')
    {
        if (flag == 0)
            value = res_val.toDouble();
        getColorCode(value);
    }

    if (isdigit(customKey))
        res_val += customKey;

    if (customKey == '*')
        res_val += '.';

    if (customKey == 'A')
    {
        value = res_val.toDouble();
        value *= 10;
        flag = 1;
    }

    if (customKey == 'B')
    {
        value = res_val.toDouble();
        value *= 100;
        flag = 1;
    }

    if (customKey == 'C')
    {
        value = res_val.toDouble();
        value *= 1000;
        flag = 1;
    }

    if (customKey == '#')
    {
        value = 0.0;
        flag = 0;
        res_val = "";
    }
}

void RGB(int red, int green, int blue)
{
    analogWrite(9, red);
    analogWrite(10, green);
    analogWrite(11, blue);
}

void getColorCode(double value)
{
    String val = String(value);
    //rgb color codes
    int colors[][3] = {
        {0, 0, 0},
        {165, 42, 42},
        {255, 0, 0},
        {255, 165, 0},
        {255, 255, 0},
        {0, 255, 0},
        {0, 0, 255},
        {238, 130, 238},
        {125, 125, 125},
        {255, 255, 255}

    };

    int pos = val.indexOf('.');
    int f_b = val[0] - '0';
    int s_b = val[1] - '0';
    String multiplier = val.substring(2, pos);
    int t_b = multiplier.length();
    RGB((colors[f_b][0]), colors[f_b][1], colors[f_b][2]);
    delay(5000);
    RGB((colors[s_b][0]), colors[s_b][1], colors[s_b][2]);
    delay(5000);
    RGB((colors[t_b][0]), colors[t_b][1], colors[t_b][2]);
    delay(5000);
    blink();
}

void blink()
{
    int flag = 1;
    while (flag < 5)
    {
        RGB(135, 206, 235);
        delay(1000);
        RGB(0, 0, 0);
        delay(1000);
        flag++;
    }
}
