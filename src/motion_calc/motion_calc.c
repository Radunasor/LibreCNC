
#if 0

#include <math.h>

float resolution = 0.00625;
int single_step = 4;
int xcurrent = 0;
int ycurrent = 0;

int xstart_real;
int ystart_real;
int xend_real;
int yend_real;
float m;
float b;
int xstep;
int ystep;
int delta_x;
int delta_y;
int flag;
int i, j;
int area;
float xshape_start;
float yshape_start;
int xcurrent_r;
int ycurrent_r;

int correction = 0;

/// circle
float teta;
float l;
float R;
int cp;
////
/////PAK BESHAAAAVAAAD////
int wait_end_shape;
/////

void circle(float xcenter, float ycenter, float radius);
void dot(float xdot, float ydot);
void linef(float xstart_calc, float ystart_calc, float xend_calc, float yend_calc);
// float abs(float gdr);

/////mesh bandi///////
// xcurrent /= (resolution * single_step);
// ycurrent /= (resolution * single_step);
// xcurrent_r = xcurrent * single_step;
// ycurrent_r = ycurrent * single_step;

void circle(float xcenter, float ycenter, float radius)
{
    float PI = 3.1415;

    teta = 2 * (PI / 100);
    l = radius * cos(teta / 2);
    R = radius + (radius - l) / 2;

    //	cp = circle part
    for (cp = 1; cp <= 100; cp++)
    {
        teta = 2 * (PI / 100) * cp;

        linef(xcurrent, ycurrent, xcenter + R * cos(teta), ycenter + R * sin(teta));
    }
}

void linef(float xstart_calc, float ystart_calc, float xend_calc, float yend_calc)
{

    m = (yend_calc - ystart_calc) / (xend_calc - xstart_calc);

    if (xstart_calc < xend_calc & ystart_calc < yend_calc)
    {
        if (0 < m & m <= 1)
            area = 1;
        if (m > 1)
            area = 2;
    }
    else if (xstart_calc > xend_calc & ystart_calc < yend_calc)
    {
        if (m <= -1)
            area = 3;
        if (-1 < m & m < 0)
            area = 4;
    }
    else if (xstart_calc > xend_calc & ystart_calc > yend_calc)
    {
        if (0 < m & m <= 1)
            area = 5;
        if (m > 1)
            area = 6;
    }
    else if (xstart_calc<xend_calc & ystart_calc> yend_calc)
    {
        if (m <= -1)
            area = 7;
        if (-1 < m & m < 0)
            area = 8;
    }
    //////right//////
    if (xstart_calc < xend_calc & ystart_calc == yend_calc)
    {
        xend_real = floor(xend_calc + 0.5);
        delta_x = (xend_real - xcurrent);
        xstep = delta_x * single_step;

        // directions

        // LPC_GPIO0->FIOSET |= 0x00000002;

        for (i = 0; i < xstep; i++)
        {
            // xstep
            // delay_us(d);
            // LPC_GPIO0->FIOSET |= 0x00000001;
            // delay_us(on_delay);
            // LPC_GPIO0->FIOCLR |= 0x00000001;
            // xcurrent_r += 1;
        }
        xcurrent += delta_x;
    }
    //////up//////
    else if (xstart_calc == xend_calc & ystart_calc < yend_calc)
    {
        yend_real = floor(yend_calc + 0.5);
        delta_y = (yend_real - ycurrent);
        ystep = delta_y * single_step;

        // directions

        // LPC_GPIO0->FIOSET |= 0x00000010;

        for (i = 0; i < ystep; i++)
        {
            // ystep
            // delay_us(d);
            // LPC_GPIO0->FIOSET |= 0x00000008;
            // delay_us(on_delay);
            // LPC_GPIO0->FIOCLR |= 0x00000008;
            ycurrent_r += 1;
        }
        ycurrent += delta_y;
    }
    //////left//////
    else if (xstart_calc > xend_calc & ystart_calc == yend_calc)
    {
        xend_real = floor(xend_calc + 0.5);
        delta_x = (xend_real - xcurrent);
        xstep = -delta_x * single_step;

        // directions

        // LPC_GPIO0->FIOCLR |= 0x00000002;

        for (i = 0; i < xstep; i++)
        {
            // xstep
            // delay_us(d);
            // LPC_GPIO0->FIOSET |= 0x00000001;
            // delay_us(on_delay);
            // LPC_GPIO0->FIOCLR |= 0x00000001;
            xcurrent_r -= 1;
        }
        xcurrent += delta_x;
    }

    //////down//////
    else if (xstart_calc == xend_calc & ystart_calc > yend_calc)
    {
        yend_real = floor(yend_calc + 0.5);
        delta_y = (yend_real - ycurrent);
        ystep = -delta_y * single_step;

        // directions

        // LPC_GPIO0->FIOCLR |= 0x00000010;

        for (i = 0; i < ystep; i++)
        {
            // ystep
            // delay_us(d);
            // LPC_GPIO0->FIOSET |= 0x00000008;
            // delay_us(on_delay);
            // LPC_GPIO0->FIOCLR |= 0x00000008;
            ycurrent_r -= 1;
        }
        ycurrent += delta_y;
    }

    ////// area 1/////
    else if (area == 1)
    {

        b = ystart_calc - m * xstart_calc;
        // directions

        // LPC_GPIO0->FIOSET |= 0x00000002;
        // LPC_GPIO0->FIOSET |= 0x00000010;

        flag = 0;

        xend_real = floor(xend_calc + 0.5);

        do
        {

            delta_x = (floor(((ycurrent + 0.5 - b) / m) + 0.5) - xcurrent);

            if (xcurrent + delta_x >= xend_real)
            {
                delta_x = (xend_real - xcurrent);
                flag = 1;
            }
            xstep = delta_x * single_step;
            for (i = 1; i <= xstep; i++)
            {
                // xstep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000001;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000001;
                xcurrent_r += 1;
            }

            xcurrent += delta_x;

            if (ycurrent + 0.5 < yend_calc)
            {
                // ystep
                for (i = 0; i < single_step; i++)
                {
                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000008;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000008;

                    ycurrent_r += 1;
                }

                ycurrent += 1;
            }
        } while (flag == 0);
    }
    //////////////////////////
    //// area 2/////
    else if (area == 2)
    {

        b = ystart_calc - m * xstart_calc;

        // directions

        // LPC_GPIO0->FIOSET |= 0x00000002;
        // LPC_GPIO0->FIOSET |= 0x00000010;

        flag = 0;

        yend_real = floor(yend_calc + 0.5);

        do
        {

            delta_y = (floor(((xcurrent + 0.5) * m + b) + 0.5) - ycurrent);

            if (ycurrent + delta_y >= yend_real)
            {
                delta_y = (yend_real - ycurrent);

                flag = 1;
            }
            ystep = delta_y * single_step;

            for (i = 1; i <= ystep; i++)
            {
                // ystep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000008;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000008;
                ycurrent_r += 1;
            }

            ycurrent += delta_y;
            if (xcurrent + 0.5 < xend_calc)
            {
                // xstep
                for (i = 0; i < single_step; i++)
                {

                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000001;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000001;

                    xcurrent_r += 1;
                }
                xcurrent += 1;
            }
        } while (flag == 0);
    }
    ////////////////////////
    ////// area 3/////
    else if (area == 3)
    {

        b = ystart_calc - m * xstart_calc;
        // directions

        // LPC_GPIO0->FIOCLR |= 0x00000002;
        // LPC_GPIO0->FIOSET |= 0x00000010;

        flag = 0;

        yend_real = floor(yend_calc + 0.5);

        do
        {

            delta_y = (floor(((xcurrent - 0.5) * m + b) + 0.5) - ycurrent);

            if (ycurrent + delta_y >= yend_real)
            {
                delta_y = (yend_real - ycurrent);

                flag = 1;
            }
            ystep = delta_y * single_step;

            for (i = 1; i <= ystep; i++)
            {
                // ystep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000008;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000008;

                ycurrent_r += 1;
            }

            ycurrent += delta_y;
            if (xcurrent - .5 > xend_calc)
            {
                // xstep
                for (i = 0; i < single_step; i++)
                {

                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000001;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000001;
                    xcurrent_r -= 1;
                }
                xcurrent -= 1;
            }
        } while (flag == 0);
    }
    //////////////////////////

    ////// area 4/////
    else if (area == 4)
    {

        b = ystart_calc - m * xstart_calc;
        // directions

        // LPC_GPIO0->FIOCLR |= 0x00000002;
        // LPC_GPIO0->FIOSET |= 0x00000010;

        flag = 0;

        xend_real = floor(xend_calc + 0.5);

        do
        {

            delta_x = (floor(((ycurrent + 0.5 - b) / m) + 0.5) - xcurrent);

            if (xcurrent + delta_x <= xend_real)
            {
                delta_x = (xend_real - xcurrent);

                flag = 1;
            }
            xstep = -delta_x * single_step;

            for (i = 1; i <= xstep; i++)
            {
                // xstep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000001;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000001;
                xcurrent_r -= 1;
            }

            xcurrent += delta_x;
            if (ycurrent + 0.5 < yend_calc)
            {
                // ystep
                for (i = 0; i < single_step; i++)
                {
                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000008;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000008;
                    ycurrent_r += 1;
                }
                ycurrent += 1;
            }
        } while (flag == 0);
    }
    //////////////////////////

    ///
    ///
    /// area 5///
    else if (area == 5)
    {

        b = ystart_calc - m * xstart_calc;
        // directions

        // LPC_GPIO0->FIOCLR |= 0x00000002;
        // LPC_GPIO0->FIOCLR |= 0x00000010;

        flag = 0;

        xend_real = floor(xend_calc + 0.5);

        do
        {

            delta_x = (floor(((ycurrent - 0.5 - b) / m) + 0.5) - xcurrent);

            if (xcurrent + delta_x <= xend_real)
            {
                delta_x = (xend_real - xcurrent);

                flag = 1;
            }
            xstep = -delta_x * single_step;
            for (i = 1; i <= xstep; i++)
            {
                // xstep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000001;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000001;
                xcurrent_r -= 1;
            }

            xcurrent += delta_x;
            if (ycurrent - 0.5 > yend_calc)
            {

                // ystep
                for (i = 0; i < single_step; i++)
                {
                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000008;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000008;
                    ycurrent_r -= 1;
                }
                ycurrent -= 1;
            }
        } while (flag == 0);
    }
    ///////////////////////////////
    //// area 6/////
    else if (area == 6)
    {

        b = ystart_calc - m * xstart_calc;

        // directions

        // LPC_GPIO0->FIOCLR |= 0x00000002;
        // LPC_GPIO0->FIOCLR |= 0x00000010;

        flag = 0;

        yend_real = floor(yend_calc + 0.5);

        do
        {

            delta_y = (floor(((xcurrent - 0.5) * m + b) + 0.5) - ycurrent);

            if (ycurrent + delta_y <= yend_real)
            {
                delta_y = (yend_real - ycurrent);

                flag = 1;
            }
            ystep = -delta_y * single_step;
            for (i = 1; i <= ystep; i++)
            {
                // ystep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000008;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000008;
                ycurrent_r -= 1;
            }

            ycurrent += delta_y;
            if (xcurrent - 0.5 > xend_calc)
            {

                // xstep
                for (i = 0; i < single_step; i++)
                {
                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000001;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000001;
                    xcurrent_r -= 1;
                }
                xcurrent -= 1;
            }
        } while (flag == 0);
    }
    ////////////////////////
    //// area 7/////
    else if (area == 7)
    {

        b = ystart_calc - m * xstart_calc;

        // directions

        // LPC_GPIO0->FIOSET |= 0x00000002;
        // LPC_GPIO0->FIOCLR |= 0x00000010;

        flag = 0;

        yend_real = floor(yend_calc + 0.5);

        do
        {

            delta_y = (floor(((xcurrent + 0.5) * m + b) + 0.5) - ycurrent);

            if (ycurrent + delta_y <= yend_real)
            {
                delta_y = (yend_real - ycurrent);

                flag = 1;
            }
            ystep = -delta_y * single_step;
            for (i = 1; i <= ystep; i++)
            {
                // ystep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000008;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000008;
                ycurrent_r -= 1;
            }

            ycurrent += delta_y;
            if (xcurrent + 0.5 < xend_calc)
            {
                // xstep
                for (i = 0; i < single_step; i++)
                {
                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000001;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000001;
                    xcurrent_r += 1;
                }
                xcurrent += 1;
            }
        } while (flag == 0);
    }
    ////////////////////////

    ////// area 8/////
    else if (area == 8)
    {

        b = ystart_calc - m * xstart_calc;
        // directions

        // LPC_GPIO0->FIOSET |= 0x00000002;
        // LPC_GPIO0->FIOCLR |= 0x00000010;

        flag = 0;

        xend_real = floor(xend_calc + 0.5);

        do
        {

            delta_x = (floor(((ycurrent - 0.5 - b) / m) + 0.5) - xcurrent);

            if (xcurrent + delta_x >= xend_real)
            {
                delta_x = (xend_real - xcurrent);

                flag = 1;
            }
            xstep = delta_x * single_step;
            for (i = 1; i <= xstep; i++)
            {
                // xstep
                // delay_us(d);
                // LPC_GPIO0->FIOSET |= 0x00000001;
                // delay_us(on_delay);
                // LPC_GPIO0->FIOCLR |= 0x00000001;
                xcurrent_r += 1;
            }

            xcurrent += delta_x;
            if (ycurrent - 0.5 > yend_calc)
            {
                // ystep
                for (i = 0; i < single_step; i++)
                {
                    // delay_us(d);
                    // LPC_GPIO0->FIOSET |= 0x00000008;
                    // delay_us(on_delay);
                    // LPC_GPIO0->FIOCLR |= 0x00000008;
                    ycurrent_r -= 1;
                }
                ycurrent -= 1;
            }
        } while (flag == 0);
    }
    //////////////////////////
}
void dot(float xdot, float ydot)
{
    // delay_us(dot_delay);
}
// void delay_us(unsigned long t)

// {
//     a = t / 4.5;
//     for (n = 0; n < a; n++)
//         ; // cycles to count
//     {
//     }
// }
/////ghadre motlagh/////
// float abs(float gdr)
// {
//     if (gdr >= 0)
//     {
//         return gdr;
//     }
//     else if (gdr < 0)
//     {
//         return -gdr;
//     }
//     return 0;
// }
///
//////binary to decimal/////////

/////////////////////////

#endif