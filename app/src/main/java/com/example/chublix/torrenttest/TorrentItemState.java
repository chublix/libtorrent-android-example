package com.example.chublix.torrenttest;

/**
 * Created by chublix on 9/29/15.
 */
public enum TorrentItemState {
    TorrentItemStateNone,
    TorrentItemStateQueuedForChecking, // The torrent is in the queue for being checked. But there currently is another torrent that are being checked. This torrent will wait for its turn.
    TorrentItemStateCheckingFiles, // The torrent has not started its download yet, and is currently checking existing files.
    TorrentItemStateDownloadingMetadata, // The torrent is trying to download metadata from peers. This assumes the metadata_transfer extension is in use.
    TorrentItemStateDownloading, // The torrent is being downloaded. This is the state most torrents will be in most of the time. The progress meter will tell how much of the files that has been downloaded.
    TorrentItemStateFinished, // In this state the torrent has finished downloading but still doesn't have the entire torrent. i.e. some pieces are filtered and won't get downloaded.
    TorrentItemStateSeeding, // In this state the torrent has finished downloading and is a pure seeder.
    TorrentItemStateAllocating, // If the torrent was started in full allocation mode, this indicates that the (disk) storage for the torrent is allocated.
    TorrentItemStateCheckingResumeData, // The torrent is currently checking the fastresume data and comparing it to the files on disk. This is typically completed in a fraction of a second, but if you add a large number of torrents at once, they will queue up.
    TorrentItemStatePause
}
