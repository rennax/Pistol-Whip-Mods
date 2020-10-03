using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MelonLoader;
using UnityEngine;

namespace Pistol_Whip_Scene_Loader
{
    public class CustomLevelDatabase
    {
        const string levelPathRoot = "Custom Levels";
        public static List<Level> levels = new List<Level>();
        public static int MaxLevelIndex { get; private set; } = 20;
        public static bool SelectedCustomLevel { get; internal set; }
        public static LevelData CurrentSelectedLevel { get; internal set; }

        public void RebuildDatabase()
        {
            levels.Clear();
            string[] levelPaths = Directory.GetDirectories(levelPathRoot);

            foreach (var path in levelPaths)
            {
                string levelText = File.ReadAllText(Path.Combine(path, "level.json"));
                //MelonLogger.Log(levelText);
                Models.LevelPacker pack = JsonConvert.DeserializeObject<Models.LevelPacker>(levelText, new EnemyActionConverter());
                Level level = new Level()
                {
                    data = pack.levelData,
                    art = pack.albumArtMetadata,
                    index = MaxLevelIndex 
                };
                MaxLevelIndex++;

                Texture2D tex = new Texture2D(2, 2);
                ImageConversion.LoadImage(tex, File.ReadAllBytes(Path.Combine(path, level.art.art)));
                level.sprite = Sprite.Create(tex, new Rect(0f, 0f, tex.width, tex.height), new Vector2(0.5f, 0.5f), 100f);

                MelonLogger.Log(string.Format("Texture size ({0}, {1})", tex.width, tex.height));
                levels.Add(level);
               
                
                MelonLogger.Log(string.Format("Found level, songName {0} length {1}", pack.levelData.description, pack.levelData.songLength));
            }
        }

        public static Level GetLevelAtLevelIndex(int levelIndex)
        {
            return levels.Find(x => x.index == levelIndex);
        }

        public static void PopulateSongSelectionUI(SongSelectionUIController ctrl)
        {
            //Assumes 3 GameMaps per level
            //Subtract the training tutorial.
            int maxLevelDataIndex = (ctrl.levelDB.GetLevels().Count - 1) / 3;
            int startPage = 6;
            int songsPerPage = 4;
            
            for (int i = 0; i < levels.Count; i++)
            {
                Level level = levels[i];
                GameObject songPanelGO = GameObject.Instantiate(ctrl.songPanelUIControllerList[15].gameObject);
                SongPanelUIController songPanel = songPanelGO.GetComponent<SongPanelUIController>();
                songPanelGO.transform.parent = ctrl.songPanelUIControllerList[15].gameObject.transform.parent;
                Vector3 pos = ctrl.songPanelUIControllerList[15].gameObject.transform.position;
                songPanelGO.transform.position = new Vector3((1.24001f * level.index)-(1.24001f*2), pos.y, pos.z);


                songPanel.levelDataIndex = level.index;
                songPanel.songImage.sprite = level.sprite;
                //songPanel.songName.SetText(level.data.songName);

                MelonLogger.Log("Created songPanel at index: " + songPanel.levelDataIndex);


            
                ctrl.songPanelUIControllerList.Add(songPanel);
                ctrl.songPanelUIControllerGameObjectsList.Add(songPanelGO);
                int page = startPage + (int)Math.Floor((float)i / (float)songsPerPage);
                ctrl.nameToPage.Add(level.data.songName, page);
                ctrl.panelChildCount++;       
            }
        }

        public static void AddPageIndicators(SongSelectionUIController ctrl)
        {
            int songsPerPage = 4;
            int indicatorCount = (int)System.Math.Ceiling((float)levels.Count / (float)songsPerPage);

            for (int i = 0; i < indicatorCount; i++)
            {

                GameObject center = new GameObject();
                center.transform.parent = ctrl.pageCentersList[0].transform.parent;
                RectTransform rect = center.AddComponent<RectTransform>();


                float updates = ctrl.pageCentersList[2].position.x - ctrl.pageCentersList[1].position.x;
                float xpos = ctrl.pageCentersList[4].anchoredPosition.x;

                rect.anchoredPosition = new Vector2(xpos + updates * (i + 1), 0);
                rect.anchoredPosition3D = new Vector3(ctrl.pageCentersList[4].anchoredPosition3D.x + updates * (i + 1), 0);//ctrl.pageCentersList[ctrl.pageCentersList.Count - 1].anchoredPosition3D + ctrl.centerPosDelta;
                rect.anchorMax = new Vector2(0, 0);
                rect.anchorMin = new Vector2(0, 0);
                rect.offsetMin = new Vector2(ctrl.pageCentersList[4].offsetMin.x + updates * (i + 1), 0);
                rect.offsetMax = new Vector2(ctrl.pageCentersList[4].offsetMax.x + updates * (i + 1), 0);
                rect.pivot = new Vector2(0.5f, 0.5f);
                rect.sizeDelta = new Vector2(-0.16f, 0);//ctrl.centerPosDelta;
                ctrl.pageCentersList.Add(rect);


                GameObject indicator = GameObject.Instantiate(ctrl.songSelPaginatedIndicator.pageMarkers[0].gameObject);
                indicator.transform.position = new Vector3(0, 1.234978f, 4.965f);
                indicator.hideFlags |= HideFlags.DontUnloadUnusedAsset;
                indicator.transform.parent = ctrl.songSelPaginatedIndicator.pageMarkers[0].transform.parent;
                ctrl.songSelPaginatedIndicator.pageMarkers.Add(indicator.GetComponent<RectTransform>());
            }
        }
    }

    public class Level
    {
        public Models.AlbumArtMetadata art;
        public Models.LevelData data;
        public Sprite sprite;
        public int index;
    }
}
