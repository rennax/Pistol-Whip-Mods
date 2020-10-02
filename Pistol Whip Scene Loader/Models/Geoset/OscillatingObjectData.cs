using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public class OscillatingObjectData
	{
		[JsonProperty]
		public Vector3 restPoint;
		[JsonProperty]
		public float moveScale;
		[JsonProperty]
		public float phase;
	}
}