using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Pistol_Whip_Scene_Loader
{
    public class EnemyActionConverter : JsonConverter
    {
        public override bool CanConvert(Type objectType)
        {
            return typeof(Models.EnemyAction).IsAssignableFrom(objectType);
        }

        public override object ReadJson(JsonReader reader,
            Type objectType, object existingValue, JsonSerializer serializer)
        {
            JObject j = JObject.Load(reader);

            // Using a nullable bool here in case "is_album" is not present on an item
            int? type = (int?)j["actionType"];

            Models.EnemyAction action = null;
            switch (type)
            {
                case 0:
                    action = new Models.EnemyActionWait();
                    break;
                case 1:
                    action = new Models.EnemyActionMove();
                    break;
                case 2:
                    action = new Models.EnemyActionAimStart();
                    break;
                case 3:
                    action = new Models.EnemyActionAimStop();
                    break;
                case 4:
                    action = new Models.EnemyActionFire();
                    break;
                case 5:
                    action = new Models.EnemyActionAimAndFire();
                    break;
                case 15:
                    action = new Models.EnemyActionStopFiring();
                    break;
            }

            serializer.Populate(j.CreateReader(), action);

            return action;
        }

        public override bool CanWrite
        {
            get { return false; }
        }

        public override void WriteJson(JsonWriter writer,
            object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }
}
