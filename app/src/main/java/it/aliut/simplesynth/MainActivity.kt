package it.aliut.simplesynth

import android.graphics.Point
import android.os.Bundle
import android.view.MotionEvent
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        startEngine()
    }

    private external fun touchEvent(pointerId: Int, action: Int)

    private external fun startEngine()

    private external fun stopEngine()

    private external fun setFrequency(pointerId: Int, frequency: Double)

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        event?.let {
            println("--->> id: ${event.getPointerId(0)}")
            println("--->> find id: ${event.findPointerIndex(0)}")

            val pointerId = event.getPointerId(0)

            if (event.actionMasked == MotionEvent.ACTION_MOVE) {
                setFrequency(
                    pointerId,
                    getFrequency(event)
                )
            }

            touchEvent(
                pointerId,
                event.actionMasked
            )

            return true
        }

        return super.onTouchEvent(event)
    }

    private fun getFrequency(event: MotionEvent): Double {
        val size = Point()
        windowManager.defaultDisplay.getSize(size)

        return (100.0 * event.y) / size.y
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
