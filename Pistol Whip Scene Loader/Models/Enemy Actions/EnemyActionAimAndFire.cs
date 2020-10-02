using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public class EnemyActionAimAndFire : EnemyAction
	{
		[JsonProperty]
		public override int actionType { get { return 5; } }
		[JsonProperty]
		public float actionDuration;
		[JsonProperty]
		public bool stopFacingOnExit;
		[JsonProperty]
		public bool stopLookingOnExit;
		[JsonProperty]
		public float fireTime;
	}
}