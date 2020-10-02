using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


namespace Models
{
    public class EnemyActionWait : EnemyAction
    {
        [JsonProperty]
        public override int actionType { get { return 0; } }
        [JsonProperty]
        public float waitTime;
    }
}