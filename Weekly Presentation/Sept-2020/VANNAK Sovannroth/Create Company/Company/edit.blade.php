@extends('admin::layouts.master')
@section('header')
    <strong>Edit Company</strong>
@endsection
@section('content')
<form method="POST" action="{{route('company.save')}}" enctype="multipart/form-data">
    @csrf
    <div class="card card-gray">
        <div class="toolbox">
            <button class="btn btn-primary btn-sm btn-oval">
                <i class="fa fa-save"></i> Save
            </button>
        </div>
        <div class="card-block">
            @component('admin::coms.alert')
            @endcomponent
            <div class="row">
                <div class="col-sm-7">
                    <div class="form-group row">
                        <label class="col-sm-3">Name <span class="text-danger">*</span></label>
                        <div class="col-sm-9">
                            <input type="text" class="form-control" id="name" name="name" required
                                value="{{$com->name}}">
                        </div>
                    </div>
                    <div class="form-group row">
                        <label class="col-sm-3">Phone</label>
                        <div class="col-sm-9">
                            <input type="text" class="form-control" id="phone" name="phone"
                                value="{{$com->phone}}">
                        </div>
                    </div>
                    <div class="form-group row">
                        <label class="col-sm-3">Email</label>
                        <div class="col-sm-9">
                            <input type="text" class="form-control" id="email" name="email" 
                                value="{{$com->email}}">
                        </div>
                    </div>
                    <div class="form-group row">
                        <label class="col-sm-3">Address</label>
                        <div class="col-sm-9">
                            <input type="text" class="form-control" id="address" name="address"
                                value="{{$com->address}}">
                        </div>
                    </div>
                </div>
                <div class="col-sm-5">
                    <div class="form-group row">
                        <label class="col-sm-3">Logo</label>
                        <div class="col-sm-9">
                            <input type="file" class="form-control" id="photo" name="photo" accept="image/*"
                                onchange="preview(event)">
                            <div style="margin-top: 9px">
                                <img src="{{asset($com->logo)}}" alt="" id="img" width="120">
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <div class="row">
                <div class="col-sm-12">
                    <p>
                        <strong>Description</strong>
                    </p>
                    <textarea name="description" id="description" cols="30" 
                        rows="3" class="form-control">{{$com->description}}</textarea>
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
            $('#menu_company').addClass('active');
        });
        function preview(evt)
        {
            let img = document.getElementById('img');
            img.src = URL.createObjectURL(evt.target.files[0]);
        }
    </script>
@endsection
