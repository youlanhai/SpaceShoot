package com.epicgames.ue4;

import com.youlanhai.spaceshoot.OBBDownloaderService;
import com.youlanhai.spaceshoot.DownloaderActivity;


public class DownloadShim
{
	public static OBBDownloaderService DownloaderService;
	public static DownloaderActivity DownloadActivity;
	public static Class<DownloaderActivity> GetDownloaderType() { return DownloaderActivity.class; }
}

