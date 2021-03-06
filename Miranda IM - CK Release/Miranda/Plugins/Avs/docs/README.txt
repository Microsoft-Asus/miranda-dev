	Load avatars 0.0.1.0
        --------------------
        
This is a SERVICE plugin, which means, it doesn't provide anything useful 
on its own except for a few service(s) and event(s) which can be used by 
other plugins.

What it does?
-------------

It loads avatars on demand and maintains an internal cache of avatar 
bitmap handles. It also handles avatar changes transparently and can 
notify event subscribers about avatar changes.

How it works?
-------------

The service MS_AV_GETAVATARBITMAP returns a pointer to a cache entry, if an 
avatar is present for that contact. The service MAY return 0, in which 
case, there is no valid avatar yet. However, that doesn't mean there 
isn't ANY avatar, just that the avatar is not yet ready for use. When 
someone calls the service requesting an avatar, the plugin will try 
to get the avatar (if possible) and notify all subscribers via a 
hookable event as soon as the avatar is ready. If the avatar is 
already in the cache, it simply returns the cached entry.

Whenever an avatar changes, the plugin fires an event, passing the 
contacts handle in wParam and a data structure with the avatar information 
in lParam. Plugins which use the bitmap handles returned by 
MS_AV_GETAVATARBITMAP MUST subscribe to ME_AV_AVATARCHANGED, because the 
original bitmap handle may become invalid when the avatar changes.

Fetching avatars is done in a separate thread with reasonable delays to 
avoid getting into troubles with flood protection(s). Avatars are cached
"in memory".


The included clist_nicer_plus.dll is a demonstration of how the avatar 
service works and can be used by developers. Having a central instance 
which maintains avatars saves resources and increases performance.


// example, how to use it (FOR DEVS only)

#include "m_avatars.h"

struct avatarCacheEntry *ace = 0;
HBITMAP hbmAvatar = 0;

ace = (struct avatarCacheEntry *)CallService(MS_AV_GETAVATARBITMAP, (WPARAM)hContact, 0);

/*
   now, check the return value. if it is 0, then the avatar is not yet ready or unavailble
   for that contact. if it was only "not ready", your plugin will be notified by the
   hookable event ME_AV_AVATARCHANGED
   
   if the return value is != 0, then it is a valid bitmap handle. DON'T DESTROY IT IN YOUR CODE
*/


/*
 * event function
 * initialise with:
 * HANDLE hEvent = HookEvent(ME_AV_AVATARCHANGED, AvatarChanged);
 */
 
static int AvatarChanged(WPARAM wParam, LPARAM lParam)
{
        struct avatarCacheEntry *ace = (struct avatarCacheEntry *)lParam;
        HANDLE hContact = (HANDLE)wParam;
        
        if(ace == NULL)
                return 0;
        if(ace->cbSize != sizeof(struct avatarCacheEntry))
                return 0;               // safety check(s)

        HBITMAP hbmAvatar = ace->hbmPic;
        ...
        ...                
}


TODO: maybe more intelligent cache managment, including auto-expire of avatars which
      have not been used for a while.
      

Copyright and license:
----------------------

This plugin is released under the terms of the GNU general public license V2 or any later
version. 

Written, 2005 by Nightwish, silvercircle@gmail.com
