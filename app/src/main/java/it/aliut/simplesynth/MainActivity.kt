package it.aliut.simplesynth

import android.graphics.Point
import android.os.Bundle
import android.view.MotionEvent
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private val lowestFreq = 28.5 // lowest piano freq
    private val highestFreq = 4186 // highest piano freq

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        startEngine()
    }

    private external fun touchEvent(action: Int)

    private external fun startEngine()

    private external fun stopEngine()

    private external fun setFrequency(frequency: Double)

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        event?.let {
            setFrequency(getFrequency(event))
            touchEvent(event.action)
        }

        return super.onTouchEvent(event)
    }

    private fun getFrequency(event: MotionEvent): Double {
        val size = Point()
        windowManager.defaultDisplay.getSize(size)

        return lowestFreq + ((highestFreq * event.y) / size.y)
    }

    override fun onDestroy() {
        stopEngine()
        super.onDestroy()
    }

    companion object {

        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}
