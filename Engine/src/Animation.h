#pragma once
#include "Object.h"
#include "Collections.h"

struct Key
{
    float time;
    float value;
	
	float tangent;

	Key(float time, float value): time(time), value(value)
    {
    }
};

class KeyFraming
{
public:
    List<Key> keys;
    float alpha;
    // constructor
    KeyFraming() {
    	alpha=1.5f;
    };

    // set k'th key
    void SetKey(int k, float time, float value) {
        keys[k].time = time;
        keys[k].value = value;
    	
    };

	void AddKey(float time, float value)
	{
		keys.emplace_back(time, value);
	}

    // get value at time t by linear interpolation
    float getValLinear(float t) {
        float val = 0.0f;
        Key lastKey = keys[keys.size() - 1];
    	
        if (t > lastKey.time) {
        	return lastKey.value;
        }

        for (int k = 0; k < keys.size()-1; k++) {
            if (keys[k].time == t) return keys[k].value;
            if (t < keys[k + 1].time) {
                val = ((t - keys[k].time) / (keys[k + 1].time - keys[k].time)) *
                    (keys[k + 1].value - keys[k].value) + keys[k].value;
                break;
            }
        }

        return val;
    };

    void ComputeTangents() {
    	int lastIndex = keys.size()-1;
        keys[0].tangent = (keys[1].value - keys[0].value) / (keys[1].time - keys[0].time);
        keys[lastIndex].tangent = (keys[lastIndex].value - keys[lastIndex-1].value) / (keys[lastIndex].time - keys[lastIndex-1].time);
    	
    	for(int i=1;i<keys.size()-1;i++)
    	{
			float prevValue = keys[i-1].value;
    		float nextValue = keys[i+1].value;

    		float prevTime = keys[i-1].time;
    		float nextTime = keys[i+1].time;

            float currentTangent =(nextValue - prevValue)/(nextTime-prevTime);
    		currentTangent*=alpha;
    		keys[i].tangent = currentTangent;
    			
    	}

    	
    }

    float GetCatmullRomValue(float t) {
        float val = 0.0f;
        Key lastKey = keys[keys.size() - 1];

        if (t > lastKey.time) {
            return lastKey.value;
        }

        for (int k = 0; k < keys.size() - 1; k++) {
            if (keys[k].time == t) return keys[k].value;
            if (t < keys[k + 1].time) {
            	float s = (t - keys[k].time) / (keys[k + 1].time - keys[k].time);
            	float s2 = s*s;
            	float s3 = s2*s;
                val = (2*s3- 3*s2 +1) * keys[k].value + (s3-2*s2+s)*keys[k].tangent
            	 + (-2 * s3 + 3 * s2) * keys[k+1].value + (s3 - s2)*keys[k+1].tangent;
                break;
            }
        }

        return val;
    }

};

/*
 * Class for perform animation.
 */
class Animation:Object
{
public:
	KeyFraming xTKF;
    KeyFraming yTKF;
    KeyFraming zTKF;
	
    KeyFraming xRKF;
    KeyFraming yRKF;
    KeyFraming zRKF;

	float playTime;

	void SetKey(int k, Vector3 position, Vector3 eulerAngles, float time)
	{
        xTKF.SetKey(k, time, position.x);

        yTKF.SetKey(k, time, position.y);

        zTKF.SetKey(k, time, position.z);

        xRKF.SetKey(k, time, eulerAngles.x);

        yRKF.SetKey(k, time, eulerAngles.y);

        zRKF.SetKey(k, time, eulerAngles.z);
	}

    void AddKey(Vector3 position, Vector3 eulerAngles, float time)
    {
        xTKF.AddKey(time, position.x);

        yTKF.AddKey(time, position.y);

        zTKF.AddKey(time, position.z);

        xRKF.AddKey(time, eulerAngles.x);

        yRKF.AddKey(time, eulerAngles.y);

        zRKF.AddKey(time, eulerAngles.z);
    }

	void ComputeTangents()
	{
        xTKF.ComputeTangents();
        yTKF.ComputeTangents();
        zTKF.ComputeTangents();
        xRKF.ComputeTangents();
        yRKF.ComputeTangents();
        zRKF.ComputeTangents();
	}

	Vector3 GetPos(float time)
	{
		return Vector3(xTKF.GetCatmullRomValue(time), yTKF.GetCatmullRomValue(time),zTKF.GetCatmullRomValue(time));
	}

    Quaternion GetRotation(float time)
    {
        return QuatMath::euler(Vector3(xRKF.GetCatmullRomValue(time), yRKF.GetCatmullRomValue(time), zRKF.GetCatmullRomValue(time)));
    }

	bool IsFinished(float time)
	{
		return time>=playTime;
	}
};