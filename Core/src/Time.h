#ifndef TIME_H
#define TIME_H

class Time
{
	public:
		static void UpdateDeltaTime(double time);
		inline static const double& DeltaTime() { return _deltaTime; };
	private:
		static double _deltaTime;
};

#endif

