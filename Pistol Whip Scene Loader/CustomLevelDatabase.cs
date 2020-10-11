using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MelonLoader;
using UnityEngine;
using Pistol_Whip_Scene_Loader.Conversion;
using UnityEngine.Experimental.AssetBundlePatching;
using Il2CppSystem.Reflection;
using Harmony;

namespace Pistol_Whip_Scene_Loader
{
    public class CustomLevelDatabase
    {
        const string levelPathRoot = "Custom Levels";
        const string replaceSongPath = "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/561074166.wem";
        const string songBackupPath = "Pistol Whip_Data/StreamingAssets/Audio/GeneratedSoundBanks/Windows/561074166_backup.wem";

        public static List<Level> levels = new List<Level>();
        public static int MaxLevelIndex { get; private set; } = 20;
        public static bool SelectedCustomLevel { get; internal set; }
        public static LevelData CurrentSelectedLevel { get; internal set; }

        private static Il2CppAssetBundle assetDBCurrentLevel; //TODO unload on level end to preserve resources

        public void RebuildDatabase()
        {
            levels.Clear();
            string[] levelPaths = Directory.GetDirectories(levelPathRoot);

            foreach (var path in levelPaths)
            {
                string levelText = File.ReadAllText(Path.Combine(path, "level.json"));
                //MelonLogger.Log(levelText);
                Models.LevelPacker pack = JsonConvert.DeserializeObject<Models.LevelPacker>(levelText, new EnemyActionConverter(), new TrackSectionConverter());
                Level level = new Level()
                {
                    data = pack.levelData,
                    art = pack.albumArtMetadata,
                    index = MaxLevelIndex,
                    path = path
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


        static Dictionary<string, Il2CppAssetBundle> loadedBundles = new Dictionary<string, Il2CppAssetBundle>();

        public static void LoadAssetsForLevel(Level level, LevelData data)
        {
            /* TODO:
             * Assign props to the corresponding object and not just to level data. This should allow
             * for props made specifically for a given difficulty (more dynamic props for a given difficulty would be cool)
             */

            //TODO proper assetbundle management...
            //if (assetDBCurrentLevel != null)
            //{
            //    assetDBCurrentLevel.Unload(true);
            //}


            if (!loadedBundles.TryGetValue(Path.Combine(level.path, "props"), out assetDBCurrentLevel))
            {
                assetDBCurrentLevel = Il2CppAssetBundleManager.LoadFromFile(Path.Combine(level.path, "props"));
                loadedBundles.Add(Path.Combine(level.path, "props"), assetDBCurrentLevel);
            }

            Dictionary<string, GameObject> staticPropPrefabs = new Dictionary<string, GameObject>();
            Dictionary<string, GameObject> dynamicPropPrefabs = new Dictionary<string, GameObject>();            
            
            for (int j = 0; j < level.data.gameMaps.Length; j++)
            {
                MelonLogger.Log($" Loading props for gameMap at index {j}");
                Models.GameMap map = level.data.gameMaps[j];
                for (int i = 0; i < map.geoSet.staticProps.Count; i++)
                {
                    //MelonLogger.Log($" Loading prop at index {i} for gameMap at index {j}");
                    Models.WorldObject propSrc = map.geoSet.staticProps[i];
                    GameObject go;

                    //Keep dictionary in case object is used multiple times
                    if (!staticPropPrefabs.TryGetValue(propSrc.prefab, out go))
                    {
                        go = assetDBCurrentLevel.LoadAsset<GameObject>(propSrc.prefab);
                        var meshFilter = go.GetComponentInChildren<MeshFilter>();
                        if (meshFilter == null) 
                        {
                            MelonLogger.Log("Static prop must contain a MeshFilter");
                            continue;
                        }
                        var renderer = meshFilter.GetComponent<MeshRenderer>();
                        renderer.material = new Material(Shader.Find("Cloudhead/Universal/HighEnd/LevelGeo_Simple"));
                        renderer.enabled = true;

                        //TODO make LODSwitcher work for static props
                        //var lod = meshFilter.transform.gameObject.AddComponent<LODSwitcher>();
                        ////lod.fixedLODLevel = -1;
                        ////lod.maxLOD = 3;
                        ////lod.enabled = true;

                        //lod.lodMeshes = new Mesh[]
                        //{
                        //    meshFilter.sharedMesh
                        //};
                        //lod.staticRenderers = new GameObject[] { renderer.gameObject };
                        //lod.meshFilter = meshFilter;
                        staticPropPrefabs.Add(propSrc.prefab, go);
                    }
                    


                    WorldObject prop = new WorldObject(
                        ConversionExtension.WorldPointNative(propSrc.point),
                        go,
                        propSrc.scale
                    );
                    //data.maps[j].geoSet.staticProps.Add(prop);
                    data.simpleStaticWorldObjects.Add(prop);
                }
                for (int i = 0; i < map.geoSet.dynamicProps.Count; i++)
                {
                    Models.DynamicWorldObject propSrc = map.geoSet.dynamicProps[i];
                    GameObject go;

                    //Keep dictionary in case object is used multiple times
                    if (!dynamicPropPrefabs.TryGetValue(propSrc.prefab, out go))
                    {
                        foreach (string animClip in propSrc.animationClipNames)
                        {
                            //QUESTION: Do we need to store the clips or just load them?
                            var clip = assetDBCurrentLevel.Load<AnimationClip>(animClip);
                        }
                        RuntimeAnimatorController animController = assetDBCurrentLevel.Load<RuntimeAnimatorController>(propSrc.animatorName);
                        Animator animator;
                        LevelEventReceiver eventReceiver;

                        go = assetDBCurrentLevel.LoadAsset<GameObject>(propSrc.prefab);
                        
                        if (go.GetComponent<Animator>() == null)
                            animator = go.AddComponent<Animator>();
                        else
                            animator = go.GetComponent<Animator>();

                        animator.runtimeAnimatorController = animController;

                        if (go.GetComponent<DynamicObject>() == null)
                        {
                            go.AddComponent<DynamicObject>();
                        }

                        if (go.GetComponent<LevelEventReceiver>() == null)
                            eventReceiver = go.AddComponent<LevelEventReceiver>();
                        else
                            eventReceiver = go.GetComponent<LevelEventReceiver>();

                        eventReceiver.eventID = propSrc.eventID;
                        eventReceiver.actionType = (LevelEventReceiver.ActionType)propSrc.actionType; //NOTE: For now we only allow animatorTrigger
                        eventReceiver.animator = animator;
                        eventReceiver.animatorProperty = propSrc.animatorProperty;
                        eventReceiver.animHash = propSrc.animHash;


                        //TODO PlayerKiller component on the object containing collider.

                        //QUESTION: Should we allow mesh to be on the root of the prefab or only as a child?
                        var meshFilter = go.GetComponentInChildren<MeshFilter>();
                        var renderer = meshFilter.GetComponent<MeshRenderer>();
                        renderer.material = new Material(Shader.Find("Cloudhead/Universal/HighEnd/LevelGeo_Simple")); //TODO allow to make/load custom materials
                        renderer.enabled = true;

                        //TODO make LODSwitcher work for dynamic props

                        dynamicPropPrefabs.Add(propSrc.prefab, go);
                    }



                    WorldObject prop = new WorldObject(
                        ConversionExtension.WorldPointNative(propSrc.point),
                        go,
                        propSrc.scale
                    );
                    //data.maps[j].geoSet.staticProps.Add(prop);
                    data.simpleDynamicWorldObjects.Add(prop);
                }
            }

        }

        public static void ReplaceSong(Level level)
        {

            if (!File.Exists(songBackupPath))
            {
                File.Copy(replaceSongPath, songBackupPath);
            }

            File.Copy(Path.Combine(level.path, "song.wem"), replaceSongPath, true);
        }

        public static List<Difficulty> GetDifficultiesForLevel(Level level)
        {
            List<Difficulty> diffs = new List<Difficulty>();
            foreach (var map in level.data.gameMaps)
            {
                diffs.Add((Difficulty)map.trackData.difficulty);
            }
            return diffs;
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
        public string path;
    }
}
