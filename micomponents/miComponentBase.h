#pragma once

#include <string>
#include <memory>
#include <mi/miutils/Time.h>
#include <mi/mitasks/miTaskSync.h>

namespace micomponents
{
	class miComponentBase
	{
	protected:
		bool _Start;
		bool _DisableInputs;
		bool _DisableOutputs;
		bool _Check;
		int _Intervall;
		std::string _Name;
		miutils::Time _Time;
		mitasks::miTaskSync* _ParentTaskSync;
		int _LastTick;

	public:
		miComponentBase(const std::string name, int intervall)
			:_Start(false)
			, _DisableInputs(false)
			, _DisableOutputs(false)
			, _Check(false)
			, _Intervall(intervall)
			, _Name(name)
			, _Time()
			, _ParentTaskSync(nullptr)
			, _LastTick(0)
		{

		}

		void setParentTaskSync(mitasks::miTaskSync* parentTaskSync)
		{
			_ParentTaskSync = parentTaskSync;
		}

		virtual const std::string name();
		virtual bool componentProcess(int rootInterval, long tick);
		virtual void componentStart();
		virtual void componentStop();
		virtual void disableInputs(bool disable);
		virtual void disableOutputs(bool disable);
		virtual void check(bool check);
		virtual const std::string getValue(const std::string& name);

		void lock()
		{
			if (_ParentTaskSync != nullptr)
			{
				_ParentTaskSync->lock();
			}
		}
		void unlock()
		{
			if (_ParentTaskSync != nullptr)
			{
				_ParentTaskSync->unlock();
			}
		}
	};

	typedef std::shared_ptr<miComponentBase> miComponentBaseShared;
}

