#pragma warning disable CS8618
#pragma warning disable CS0219

using CyberpunkSdk;
using CyberpunkSdk.Types;

using CyberpunkSdk.Systems;

using CyberpunkSdk.Internal;

namespace Cyberpunk.Rpc.Server.Plugins
{
public static partial class EmoteServer
{
	[ServerRpc(Class = 16273172002596938280, Function = 8330132648100619273)]
	public static void TriggerEmote(ulong playerId, IBuffer data)
	{
		ushort length = 0;
		var name = data.ReadString();

		TriggerEmote_Impl(playerId, name);
	}

	public static partial void TriggerEmote_Impl(ulong playerId, string name);

}
}