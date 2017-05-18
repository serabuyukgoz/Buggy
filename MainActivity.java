package com.example.sera.testaccelerometer;

import android.app.Activity;
import android.content.res.Resources;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;


public class MainActivity extends Activity implements SensorEventListener {
    private SensorManager sensorManager;
    private Sensor sensorAccelerometer;
    TextView txtX, txtY,txtZ;

    float ax,ay,az;



    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sensorManager=(SensorManager) getSystemService(SENSOR_SERVICE);
        sensorAccelerometer=sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        //sensorGravity=sensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY);
        sensorManager.registerListener(this, sensorAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
        txtX = (TextView)findViewById(R.id.textX);



    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy)
    {

    }
/*
    protected void onPause()
    {
        super.onPause();
        sensorManager.unregisterListener(this);
    }

    protected void onResume()
    {
        super.onResume();
        sensorManager.registerListener(this,sensorAccelerometer, SensorManager.SENSOR_DELAY_NORMAL);
    }
    */
    @Override
    public void onSensorChanged(SensorEvent event)
    {
        /*

        double alpha = 0.8;

        gravity[0] = alpha * gravity[0] + (1 - alpha) * event.values[0];
        gravity[1] = alpha * gravity[1] + (1 - alpha) * event.values[0];
        gravity[2] = alpha * gravity[2] + (1 - alpha) * event.values[0];

        linear_acceleration[0] = event.values[0] - gravity[0];
        linear_acceleration[1] = event.values[1] - gravity[1];
        linear_acceleration[2] = event.values[2] - gravity[2];
        */
        // Accelerometer
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER)
        {
            ax=event.values[0];
            ay=event.values[1];
            az=event.values[2];

            txtX.setText(" X: " + ax + "  Y: " + ay + " Z:" + az);

        }



     }
}
