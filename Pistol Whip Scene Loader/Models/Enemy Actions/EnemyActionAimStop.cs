using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
    public class EnemyActionAimStop : EnemyAction
    {
        [JsonProperty]
        public override int actionType { get { return 3; } }
        public bool stopFacing;
        public bool stopLooking;
    }
}