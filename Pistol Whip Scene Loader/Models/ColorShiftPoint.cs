using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
	[Serializable]
	public class ColorShiftPoint
	{
		public int start;
		public int end;
		public ColorData colors;
	}

	[Serializable]
	public struct ColorData
	{
		public Color mainColor;
		public Color fogColor;
		public Color glowColor;
		public bool customEnemyColor;
		public Color storedEnemyColor;
	}
}