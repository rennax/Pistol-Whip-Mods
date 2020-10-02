using Newtonsoft.Json;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Models
{
    public class EnemyActionAimStart : EnemyAction
    {
        [JsonProperty]
        public override int actionType { get { return 2; } }
    }
}