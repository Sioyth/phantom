#ifndef TIME_H
#define TIME_H

class Time
{
	public:
		static void UpdateDeltaTime(const double& time);
		inline static const double& DeltaTime() { return _deltaTime; };
		inline static double &DeltaTimeVal() { return _deltaTime; };
	private:
		static double _deltaTime;
};

#endif

