---
theme: nmt
background: https://cover.sli.dev
title: Adafruit - Setting Up, and Using
class: text-left
drawings:
  persist: false
transition: fade
mdc: true
duration: 90min
---

# Adafruit - Setting Up and Using


<div @click="$slidev.nav.next" class="mt-12 -mx-4 p-4" hover:bg="white op-10">
<p>Press <kbd>Space</kbd> or <kbd>RIGHT</kbd> for next slide/step <fa7-solid-arrow-right /></p>
</div>

<div class="abs-br m-6 text-xl">
  <a href="https://github.com/adygcode/SaaS-FED-Notes" target="_blank" class="slidev-icon-btn">
    <fa7-brands-github class="text-zinc-300 text-3xl -mr-2"/>
  </a>
</div>


<!--
The last comment block of each slide will be treated as slide notes. It will be visible and editable in Presenter Mode along with the slide. [Read more in the docs](https://sli.dev/guide/syntax.html#notes)
-->


---
layout: default
level: 2
---

# Navigating Slides

Hover over the bottom-left corner to see the navigation's controls panel.

## Keyboard Shortcuts

|                                                     |                             |
|-----------------------------------------------------|-----------------------------|
| <kbd>right</kbd> / <kbd>space</kbd>                 | next animation or slide     |
| <kbd>left</kbd>  / <kbd>shift</kbd><kbd>space</kbd> | previous animation or slide |
| <kbd>up</kbd>                                       | previous slide              |
| <kbd>down</kbd>                                     | next slide                  |

---
layout: section
---

# Objectives

---
level: 2
layout: two-cols
---

# Objectives

::left::



::right::



---
level: 2
layout: figure-side
figureUrl: public/orly-book-cover-dashboards.png
---

# Contents

<Toc minDepth="1" maxDepth="1" />

---
layout: section
---

# 🌟 Ice Breaker

## TODO: Add ice-breaker


---
layout: section
---

# What is Adafruit

---
level: 2
---



---
layout: section
---

# Adafruit Accounts

---
level: 2
---

# Creating an Adafruit Account


---
level: 2
---

# Logging Into Your Adafruit Account



---
layout: section
---

# Adafruit and MQTT

---
level: 2
---

# Adafruit and MQTT

- remind about free account limits

---
level: 2
---

# Best Practices for "Secrets"

- store secrets in a separate `secrets.h` file
- only publish to GitHub if a private repo
- better to publish a "placeholder" version of secrets
- share secrets via other methods as needed



---
level: 2
---

# Secrets File

```cpp [C++] {1-5|7-8|10-12|14|16-18|all}
/**
 * Secrets file for MQTT & WiFi
 *
 * Name:             YOUR NAME
 */

#define IO_BROKER "io.adafruit.com"
#define IO_PORT 1883

#define IO_CLIENTNAME  "..."
#define IO_USERNAME  "...."
#define IO_KEY       "...."

#define IO_DATA_PUB     IO_USERNAME "/feeds/feed-key"

const char* WIFI_SSID = "...";      // used by init Wi-Fi
const char* WIFI_PASS = "...";      // used by init Wi-Fi
const char* hostname  = IO_BROKER ;  // used by init Wi-Fi
```

---
level: 2
---




---

# Acknowledgements & References

- TODO: Add references etc

> - Some content was generated with the assistance of Microsoft Copilot

---
layout: end
---

# Remember: 🦆

### With Laravel and Pest:

- your code can be clean,
- your tests can be sharp, and...
- according to the rubber duck:
- your sanity can remain… mostly intact.
