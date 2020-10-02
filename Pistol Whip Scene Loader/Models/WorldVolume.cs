using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	public class WorldVolume
	{
		public Vector3i position;
		public Vector3i min;
		public Vector3i max;
		public GeoVolume type;
	}

	public enum GeoVolume
	{
		Subtractive = 0,
		Additive = 1,
	}
}