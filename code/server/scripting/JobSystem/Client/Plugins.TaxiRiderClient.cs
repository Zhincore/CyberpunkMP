// This file is automatically generated

#pragma warning disable CS8618
#pragma warning disable CS0219

using CyberpunkSdk;
using CyberpunkSdk.Types;

using CyberpunkSdk.Systems;

using CyberpunkSdk.Internal;

namespace Cyberpunk.Rpc.Client.Plugins
{
public static class TaxiRiderClient
{
	[ClientRpc(Class = 14498540813421764700, Function = 16060324207638237351)]
	public static void StartTrip(ulong playerId, ulong vehicle_server_id)
	{
		ushort length = 0;
		var data = IBuffer.Create();
		try{
			data.WriteUint64(vehicle_server_id);
			CyberpunkSdk.Server.RpcManager.Call(playerId, 14498540813421764700, 16060324207638237351, data);
		} finally {
			IBuffer.Release(data);
		}
	}

	[ClientRpc(Class = 14498540813421764700, Function = 12778657023157887943)]
	public static void EndTrip(ulong playerId, bool success, uint cost)
	{
		ushort length = 0;
		var data = IBuffer.Create();
		try{
			data.WriteBool(success);
			data.WriteUint32(cost);
			CyberpunkSdk.Server.RpcManager.Call(playerId, 14498540813421764700, 12778657023157887943, data);
		} finally {
			IBuffer.Release(data);
		}
	}

}
}