using Newtonsoft.Json;
using System;
using System.Collections;
using System.Collections.Generic;
using Unity.Collections;
using UnityEngine;

namespace Models
{
    public class TargetData
    {
        public int distance = 0;

        public Vector2 placement = new Vector2(0, 0);
        
        public int enemyType;

        public WorldPoint enemyOffset;

        public EnemySequence enemySequence;

        public bool ignoreForLevelRank;

        public List<float> fireTimes = new List<float>();

        public CheevoID cheevoID;

        public bool noGround;

    }
}
