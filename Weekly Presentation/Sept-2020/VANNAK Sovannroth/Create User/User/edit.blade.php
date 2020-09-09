@extends('admin::layouts.master')
@section('header')
    <strong>Edit Users</strong>
@endsection
@section('content')
    <form action="{{route('user.update', $user->id)}}" method="POST" enctype="multipart/form-data">
        @csrf
        @method('PATCH')
        <div class="card card-gray">
            <div class="toolbox">
                <button class="btn btn-primary btn-sm btn-oval">
                    <i class="fa fa-save"></i> Save
                </button>
                <a href="{{route('user.index')}}" class="btn btn-warning btn-sm btn-oval">
                    <i class="fa fa-reply"></i> Back
                </a>
            </div>
            <div class="card-block">
                @component('admin::coms.alert')
                @endcomponent
                <div class="row">
                    <div class="col-sm-7">
                        
                        <div class="form-group row">
                            <label for="name" class="col-sm-3">Name <span class="text-danger">*</span></label>
                            <div class="col-sm-9">
                                <input type="text" class="form-control" id="name" name="name" 
                                    required autofocus value="{{$user->name}}">
                            </div>
                        </div>
                        <div class="form-group row">
                            <label for="email" class="col-sm-3">Email <span class="text-danger">*</span></label>
                            <div class="col-sm-9">
                                <input type="email" class="form-control" id="email" name="email" 
                                    required value="{{$user->email}}">
                            </div>
                        </div>
                        <div class="form-group row">
                            <label for="password" class="col-sm-3">Password</label>
                            <div class="col-sm-9">
                                <input type="password" class="form-control" id="password" name="password">
                                <p>
                                    <small>Keep it blank to use the old password!</small>
                                </p>
                            </div>
                        </div>
                    </div>
                    <div class="col-sm-5">
                        <div class="form-group row">
                            <label for="photo" class="col-sm-2">Photo</label>
                            <div class="col-sm-9">
                                <input type="file" class="form-control" id="photo" name="photo"
                                    onchange="preview(event)" accept="image/*">
                                <div style="margin-top: 9px">
                                    <img src="{{asset($user->photo)}}" alt="" id="img" width="120">
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </form>
@endsection
@section('js')
    <script>
        $(document).ready(function(){
            $('#sidebar-menu li').removeClass('active open');
            $('#sidebar-menu li ul li').removeClass('active');

            $('#menu_config').addClass('active open');
            $('#collapse_config').addClass('collapse in');
            $('#menu_user').addClass('active');
        });
        function preview(evt)
        {
            let img = document.getElementById('img');
            img.src = URL.createObjectURL(evt.target.files[0]);
        }
    </script>
@endsection