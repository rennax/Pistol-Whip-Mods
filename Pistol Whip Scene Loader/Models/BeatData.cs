using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;



namespace Models
{
 
    public class BeatData
    {
        public float time;
        public List<TargetData> targets = new List<TargetData>();
        public List<ObstacleData> obstacles = new List<ObstacleData>();
    }

}