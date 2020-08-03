	


	##OnLevelSelect(Messages.LevelSelectEvent e)
	* if e.map is null terminate.
	* Get LevelData from e.map.
	* Throw "ArgumentOutOfRangeException" if levelData.sections.size is 0
	* Get first element of sections
	* Get main color, TrackSection.get_mainColor
	* invoke virtual function get_scaleFog()
	* Create Message.SceneColorEvent via the constructor .ctor(Color color, bool scaleFog)
	* Get Messenger instance and send SceneColorEvent.