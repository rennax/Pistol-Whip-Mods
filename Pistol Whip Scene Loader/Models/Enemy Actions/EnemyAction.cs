using Newtonsoft.Json;
using System;
using System.Collections;
using System.Collections.Generic;
using Unity.Collections;
using UnityEngine;

namespace Models
{
    public class EnemyAction
    {

        public virtual int actionType { get; }

        public float duration;

        public WorldPoint localStartingPoint;

        public WorldPoint localEndingPoint;

        public float sequenceStartTime;

    }
}