<!doctype html>
<html class="no-js" lang="en">
    <head>
        <meta charset="utf-8">
        <meta http-equiv="x-ua-compatible" content="ie=edge">
        <title> Web Admin | GTR Lab </title>
        <meta name="description" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <link rel="apple-touch-icon" href="apple-touch-icon.png">
        <!-- Place favicon.ico in the root directory -->
        <link rel="stylesheet" href="{{asset('/backend/css/vendor.css')}}">
        <link rel="stylesheet" href="{{asset('/backend/css/app-green.css')}}">
        <link rel="stylesheet" href="{{asset('/backend/css/custom.css')}}">

        @yield('css')
    </head>
    <body>
        <div class="main-wrapper">
            <div class="app" id="app">
                <header class="header">
                    <div class="header-block header-block-collapse d-lg-none d-xl-none">
                        <button class="collapse-btn" id="sidebar-collapse-btn">
                            <i class="fa fa-bars"></i>
                        </button>
                    </div>
                    <div class="header-block header-block-search">
                        @yield('header')
                    </div>
                   
                    <div class="header-block header-block-nav">
                        <ul class="nav-profile">
                            
                            <li class="profile dropdown">
                                <a class="nav-link dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
                                    <div class="img" style="background-image: url('{{asset(Auth::user()->photo)}}')">
                                    </div>
                                    <span class="name"> {{Auth::user()->name}} </span>
                                </a>
                                <div class="dropdown-menu profile-dropdown-menu" aria-labelledby="dropdownMenu1">
                                    <a class="dropdown-item" href="#">
                                        <i class="fa fa-user icon"></i> Profile </a>
                                    
                                    <a class="dropdown-item" href="{{route('user.reset')}}">
                                        <i class="fa fa-reply icon"></i> Reset Password </a>
                                    <div class="dropdown-divider"></div>
                                    <a class="dropdown-item" href="{{route('user.logout')}}">
                                        <i class="fa fa-power-off icon"></i> Logout </a>
                                </div>
                            </li>
                        </ul>
                    </div>
                </header>
                <aside class="sidebar">
                    <div class="sidebar-container">
                        <div class="sidebar-header">
                            <div class="brand">
                                <div class="logo">
                                    <img src="{{asset('backend/logo.png')}}" alt="" width="35">
                                </div> GTR Lab
                            </div>
                        </div>
                        <nav class="menu">
                            <ul class="sidebar-menu metismenu" id="sidebar-menu">
                                <li id="menu_home">
                                    <a href="{{url('admin/')}}">
                                        <i class="fa fa-home"></i> Dashboard </a>
                                </li>
                                <li id="menu_slide">
                                    <a href="{{route('slide.index')}}">
                                        <i class="fa fa-star"></i> Slides </a>
                                </li>
                                <li id="menu_about">
                                    <a href="{{route('about.index')}}">
                                        <i class="fa fa-th"></i> Abouts </a>
                                </li>
                                <li id="menu_page">
                                    <a href="{{route('page.index')}}">
                                        <i class="fa fa-file"></i> Pages </a>
                                </li>
                                <li id="menu_feature">
                                    <a href="{{route('feature.index')}}">
                                        <i class="fa fa-bell"></i> Features </a>
                                </li>
                                <li id="menu_config">
                                    <a href="">
                                        <i class="fa fa-cog"></i> Settings <i class="fa arrow"></i>
                                    </a>
                                    <ul class="sidebar-nav" id="collapse_config">
                                        <li id="menu_company">
                                            <a href="{{route('company.index')}}">
                                                <i class="fa fa-arrow-right"></i> Company
                                            </a>
                                        </li>
                                        <li id="menu_category">
                                            <a href="{{route('category.index')}}">
                                                <i class="fa fa-arrow-right"></i> Categories
                                            </a>
                                        </li>
                                        <li id="menu_social">
                                            <a href="{{route('social.index')}}">
                                                <i class="fa fa-arrow-right"></i> Socials
                                            </a>
                                        </li>
                                        <li id="menu_user">
                                            <a href="{{route('user.index')}}">
                                                <i class="fa fa-arrow-right"></i> Users
                                            </a>
                                        </li>
                                        
                                    </ul>
                                </li>
             
                            </ul>
                        </nav>
                    </div>
                    <footer class="sidebar-footer">
                        <ul class="sidebar-menu metismenu" id="customize-menu">
                            <li>
                                <ul>
                                    <li class="customize">
                                        <div class="customize-item">
                                            <div class="row customize-header">
                                                <div class="col-4">
                                                </div>
                                                <div class="col-4">
                                                    <label class="title">fixed</label>
                                                </div>
                                                <div class="col-4">
                                                    <label class="title">static</label>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-4">
                                                    <label class="title">Sidebar:</label>
                                                </div>
                                                <div class="col-4">
                                                    <label>
                                                        <input class="radio" type="radio" name="sidebarPosition" value="sidebar-fixed">
                                                        <span></span>
                                                    </label>
                                                </div>
                                                <div class="col-4">
                                                    <label>
                                                        <input class="radio" type="radio" name="sidebarPosition" value="">
                                                        <span></span>
                                                    </label>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-4">
                                                    <label class="title">Header:</label>
                                                </div>
                                                <div class="col-4">
                                                    <label>
                                                        <input class="radio" type="radio" name="headerPosition" value="header-fixed">
                                                        <span></span>
                                                    </label>
                                                </div>
                                                <div class="col-4">
                                                    <label>
                                                        <input class="radio" type="radio" name="headerPosition" value="">
                                                        <span></span>
                                                    </label>
                                                </div>
                                            </div>
                                            <div class="row">
                                                <div class="col-4">
                                                    <label class="title">Footer:</label>
                                                </div>
                                                <div class="col-4">
                                                    <label>
                                                        <input class="radio" type="radio" name="footerPosition" value="footer-fixed">
                                                        <span></span>
                                                    </label>
                                                </div>
                                                <div class="col-4">
                                                    <label>
                                                        <input class="radio" type="radio" name="footerPosition" value="">
                                                        <span></span>
                                                    </label>
                                                </div>
                                            </div>
                                        </div>
                                        <div class="customize-item">
                                            <ul class="customize-colors">
                                                <li>
                                                    <span class="color-item color-red" data-theme="red"></span>
                                                </li>
                                                <li>
                                                    <span class="color-item color-orange" data-theme="orange"></span>
                                                </li>
                                                <li>
                                                    <span class="color-item color-green active" data-theme=""></span>
                                                </li>
                                                <li>
                                                    <span class="color-item color-seagreen" data-theme="seagreen"></span>
                                                </li>
                                                <li>
                                                    <span class="color-item color-blue" data-theme="blue"></span>
                                                </li>
                                                <li>
                                                    <span class="color-item color-purple" data-theme="purple"></span>
                                                </li>
                                            </ul>
                                        </div>
                                    </li>
                                </ul>
                                <a href="">
                                    <i class="fa fa-cog"></i> Customize </a>
                            </li>
                        </ul>
                    </footer>
                </aside>
                <div class="sidebar-overlay" id="sidebar-overlay"></div>
                <div class="sidebar-mobile-menu-handle" id="sidebar-mobile-menu-handle"></div>
                <div class="mobile-menu-handle"></div>
                <article class="content dashboard-page">
                    <section class="section">
                        @yield('content')
                    </section>
                </article>
                <footer class="footer">
                  
                    <div class="footer-block author">
                        <ul>
                            <li> created by <a href="https://github.com/modularcode">Sovannroth</a>
                            </li>
                           
                        </ul>
                    </div>
                </footer>
                
               
            </div>
        </div>
        <!-- Reference block for JS -->
        <div class="ref" id="ref">
            <div class="color-primary"></div>
            <div class="chart">
                <div class="color-primary"></div>
                <div class="color-secondary"></div>
            </div>
        </div>
        <script src="{{asset('backend/js/vendor.js')}}"></script>
        <script src="{{asset('backend/js/app.js')}}"></script>
        <script>
            var burl = "{{url('/')}}";
        </script>
        @yield('js')
    </body>
</html>