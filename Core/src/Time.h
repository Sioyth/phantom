#ifndef TIME_H
#define TIME_H

class Time
{
	public:
		static void UpdateDeltaTime(float time);
		inline static float DeltaTime() { return _deltaTime; };
	private:
		static float _deltaTime;
};

#endif

