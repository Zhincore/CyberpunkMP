#pragma once

#include "Core/Hooking/Detail.hpp"
#include "Core/Hooking/HookingDriver.hpp"

namespace Core
{
class HookingAgent
{
protected:
    template <typename TTarget, typename TCallback, HookFlow TFlow = HookFlow::Original, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<TFlow, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool Hook(TCallback&& aCallback, typename TTarget::Callable* aOriginal = nullptr)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, TFlow, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(std::move(aCallback)), aOriginal);
    }

    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool HookBefore(TCallback&& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::Before, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(std::move(aCallback)));
    }

    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool HookMainThread(TCallback&& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::MainThread, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(std::move(aCallback)));
    }

    template<typename TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Before, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool HookOnceBefore(TCallback&& aCallback)
    {
        return HookBefore<TTarget, TCallback, HookRun::Once>(std::move(aCallback));
    }
    
    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::After, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool HookAfter(TCallback&& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::After, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(std::move(aCallback)));
    }
    
    template<typename TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::After, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool HookOnceAfter(TCallback&& aCallback)
    {
        return HookAfter<TTarget, TCallback, HookRun::Once>(std::move(aCallback));
    }
    
    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Wrap, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool HookWrap(TCallback&& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::Wrap, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(std::move(aCallback)));
    }
    
    template<typename TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Wrap, TTarget, TCallback>::IsCompatibleNonMember
    inline static bool HookWrapOnce(TCallback&& aCallback)
    {
        return HookWrap<TTarget, TCallback, HookRun::Once>(std::move(aCallback));
    }

    template<typename TTarget, typename TCallback, HookFlow TFlow = HookFlow::Original, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<TFlow, TTarget, TCallback>::IsCompatibleMember
    inline bool Hook(const TCallback& aCallback, typename TTarget::Callable* aOriginal = nullptr)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, TFlow, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(aCallback, this), aOriginal);
    }
    
    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, TTarget, TCallback>::IsCompatibleMember
    inline bool HookBefore(const TCallback& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::Before, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(aCallback, this));
    }

    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, TTarget, TCallback>::IsCompatibleMember
    inline bool HookMainThread(const TCallback& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::MainThread, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(aCallback, this));
    }
    
    template<typename TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Before, TTarget, TCallback>::IsCompatibleMember
    inline bool HookOnceBefore(const TCallback& aCallback)
    {
        return HookBefore<TTarget, TCallback, HookRun::Once>(aCallback);
    }
    
    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::After, TTarget, TCallback>::IsCompatibleMember
    inline bool HookAfter(const TCallback& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::After, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(aCallback, this));
    }
    
    template<typename TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::After, TTarget, TCallback>::IsCompatibleMember
    inline bool HookOnceAfter(const TCallback& aCallback)
    {
        return HookAfter<TTarget, TCallback, HookRun::Once>(aCallback);
    }
    
    template<typename TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Wrap, TTarget, TCallback>::IsCompatibleMember
    inline bool HookWrap(const TCallback& aCallback)
    {
        using Wrapper = Detail::HookWrapper<TCallback>;
        using Handler = Detail::HookHandler<TTarget, Wrapper, HookFlow::Wrap, TRun>;
        return Handler::Attach(HookingDriver::GetDefault(), Wrapper(aCallback, this));
    }
    
    template<typename TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Wrap, TTarget, TCallback>::IsCompatibleMember
    inline bool HookWrapOnce(const TCallback& aCallback)
    {
        return HookWrap<TTarget, TCallback, HookRun::Once>(aCallback);
    }

    template<typename TTarget>
    inline static bool Unhook()
    {
        using Instance = Detail::HookInstance<TTarget>;
        return Instance::Detach();
    }

    template<typename TTarget>
    inline static bool IsHooked()
    {
        using Instance = Detail::HookInstance<TTarget>;
        return Instance::IsAttached();
    }

    template<RawFunc TTarget, typename TCallback, HookFlow TFlow = HookFlow::Original, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<TFlow, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool Hook(TCallback&& aCallback, typename decltype(TTarget)::Callable* aOriginal = nullptr)
    {
        return Hook<decltype(TTarget), TCallback, TFlow, TRun>(std::move(aCallback), aOriginal);
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool HookBefore(TCallback&& aCallback)
    {
        return HookBefore<decltype(TTarget), TCallback, TRun>(std::move(aCallback));
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool HookMainThread(TCallback&& aCallback)
    {
        return HookMainThread<decltype(TTarget), TCallback, TRun>(std::move(aCallback));
    }

    template<RawFunc TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Before, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool HookOnceBefore(TCallback&& aCallback)
    {
        return HookBefore<decltype(TTarget), TCallback, HookRun::Once>(std::move(aCallback));
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::After, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool HookAfter(TCallback&& aCallback)
    {
        return HookAfter<decltype(TTarget), TCallback, TRun>(std::move(aCallback));
    }

    template<RawFunc TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::After, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool HookOnceAfter(TCallback&& aCallback)
    {
        return HookAfter<decltype(TTarget), TCallback, HookRun::Once>(std::move(aCallback));
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Wrap, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool HookWrap(TCallback&& aCallback)
    {
        return HookWrap<decltype(TTarget), TCallback, TRun>(std::move(aCallback));
    }

    template<RawFunc TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Wrap, decltype(TTarget), TCallback>::IsCompatibleNonMember
    inline static bool HookWrapOnce(TCallback&& aCallback)
    {
        return HookWrap<decltype(TTarget), TCallback, HookRun::Once>(std::move(aCallback));
    }

    template<RawFunc TTarget, typename TCallback, HookFlow TFlow = HookFlow::Original, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<TFlow, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool Hook(const TCallback& aCallback, typename decltype(TTarget)::Callable* aOriginal = nullptr)
    {
        return Hook<decltype(TTarget), TCallback, TFlow, TRun>(aCallback, aOriginal);
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool HookBefore(const TCallback& aCallback)
    {
        return HookBefore<decltype(TTarget), TCallback, TRun>(aCallback);
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Before, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool HookMainThread(const TCallback& aCallback)
    {
        return HookMainThread<decltype(TTarget), TCallback, TRun>(aCallback);
    }

    template<RawFunc TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Before, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool HookOnceBefore(const TCallback& aCallback)
    {
        return HookBefore<decltype(TTarget), TCallback, HookRun::Once>(aCallback);
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::After, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool HookAfter(const TCallback& aCallback)
    {
        return HookAfter<decltype(TTarget), TCallback, TRun>(aCallback);
    }

    template<RawFunc TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::After, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool HookOnceAfter(const TCallback& aCallback)
    {
        return HookAfter<decltype(TTarget), TCallback, HookRun::Once>(aCallback);
    }

    template<RawFunc TTarget, typename TCallback, HookRun TRun = HookRun::Default>
    requires Detail::HookFlowTraits<HookFlow::Wrap, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool HookWrap(const TCallback& aCallback)
    {
        return HookWrap<decltype(TTarget), TCallback, TRun>(aCallback);
    }

    template<RawFunc TTarget, typename TCallback>
    requires Detail::HookFlowTraits<HookFlow::Wrap, decltype(TTarget), TCallback>::IsCompatibleMember
    inline bool HookWrapOnce(const TCallback& aCallback)
    {
        return HookWrap<decltype(TTarget), TCallback, HookRun::Once>(aCallback);
    }

    template<RawFunc TTarget>
    inline static bool Unhook()
    {
        return Unhook<decltype(TTarget)>();
    }

    template<RawFunc TTarget>
    inline static bool IsHooked()
    {
        return IsHooked<decltype(TTarget)>();
    }

    static HookingDriver& GetHookingDriver();

private:
    friend HookingDriver;

    static void SetHookingDriver(HookingDriver& aDriver);
};
}
