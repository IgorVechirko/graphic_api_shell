#include "WorkingScope.h"


namespace GAS
{

	WorkingScope::WorkingScope()
		: WorkingScope(nullptr)
	{
	}

	WorkingScope::WorkingScope( WorkingScopeDelegate* scope_delegate )
		: scene_( nullptr )
	{
		// in any way create delegate to prevent in future pointer checking
		delegate_.reset( scope_delegate ? scope_delegate : new WorkingScopeDelegate() );
		delegate_->setScope( this );

		auto factory = delegate_->createFactoryHook(this);
		factory_.reset( factory ? factory : createFactory() );

		d3d_context_.reset( factory_->createD3DContext() );
		d3d_context_->setScope(this);
		d3d_context_->init();

		creator_.reset( factory_->createObjectsCreator() );
		creator_->setScope(this);

		auto_release_pool_.reset( factory_->createAutoReleasePool() );
		auto_release_pool_->setScope(this);

		scheduler_.reset( factory_->createScheduler() );
		scheduler_->setScope(this);

		file_utils_.reset( factory_->createFileUtils() );
		file_utils_->setScope( this );

		threads_pool_.reset( factory_->createThreadsPool() );
		threads_pool_->setScope( this );
	}

	WorkingScope::~WorkingScope()
	{
		if ( scene_ )
			scene_->release();

		scene_ = nullptr;
	}

	int WorkingScope::run()
	{
		delegate_->onBeforeRun();

		return 0;
	}
	
	FactoryBase* WorkingScope::getFactory() const
	{
		return  factory_.get();
	}

	ScopeObjectsCreator* WorkingScope::getCreator() const
	{
		return creator_.get();
	}

	AutoReleasePool* WorkingScope::getReleasePool() const
	{
		return auto_release_pool_.get();
	}

	WorkingScopeDelegate* WorkingScope::getDelegate() const
	{
		return delegate_.get();
	}

	Scheduler* WorkingScope::getScheduler() const
	{
		return scheduler_.get();
	}

	FileUtils* WorkingScope::getFileUtils() const
	{
		return file_utils_.get();
	}

	ThreadsPool* WorkingScope::getThreadsPool() const
	{
		return threads_pool_.get();
	}

	D3DContext* WorkingScope::getD3DContext() const
	{
		return d3d_context_.get();
	}

	void WorkingScope::setScene( SceneBase* scene )
	{
		std::unique_lock scene_lock(scene_lock_);

		if ( scene_ )
			scene_->release();

		scene_ = scene;

		if ( scene_ )
			scene_->retain();
	}
	
	AutoRef<SceneBase> WorkingScope::getScene() const
	{
		std::shared_lock scene_lock(scene_lock_);
		
		auto ret = scene_;
		return ret;
	}
}